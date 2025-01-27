#include "draw.h"

Draw::Draw(Window* window) {
    this->_window = window;

    // Create a default shader
    std::string vertex = "#version 330 core\n"
                         "layout(location = 0) in vec2 position;\n"
                         "layout(location = 1) in vec2 texCoord;\n"
                         "layout(location = 2) in vec4 color;\n"
                         "uniform mat4 projection;\n"
                         "uniform mat4 view;\n"
                         "uniform mat4 model;\n"
                         "out vec2 vTexCoord;\n"
                         "out vec4 vColor;\n"
                         "void main() {\n"
                         "    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);\n"
                         "    vTexCoord = texCoord;\n"
                         "    vColor = color;\n"
                         "}\n";

    std::string fragment = "#version 330 core\n"
                           "in vec2 vTexCoord;\n"
                           "in vec4 vColor;\n"
                           "out vec4 color;\n"
                           "uniform sampler2D tex;\n"
                           "uniform bool textured;\n"
                           "uniform vec4 tint;\n"
                           "void main() {\n"
                           "    if(textured)\n"
                           "         color = texture(tex, vTexCoord) * tint;\n"
                           "    else\n"
                           "         color = tint;\n"
                           "}\n";

    _defaultFill2d = new Shader<Vertex2D>(vertex.c_str(), fragment.c_str(),
                                          {.alphaMode = ALPHA_MODE_BLEND, .cullMode = CULL_MODE_NONE, .depthMode = DEPTH_MODE_NEVER});
    _defaultLine2d = new Shader<Vertex2D>(vertex.c_str(), fragment.c_str(),
                                          {.renderMode = RENDER_MODE_WIRE_FRAME, .topologyMode = TOPOLOGY_MODE_LINE_STRIP});

    _quad = Mesh<Vertex2D, uint32_t>::quad(Vector2::one);
    _line = new Mesh<Vertex2D, uint32_t>();

    _camera2d = nullptr;
}

void Draw::begin() {
    Window::_current = _window;
    glfwMakeContextCurrent(_window->_window);
    //glBindFramebuffer(GL_FRAMEBUFFER, this->window->_framebuffer);
    //glViewport(0, 0, this->window->_size.x, this->window->_size.y);
}

void Draw::end() {
    glfwSwapBuffers(_window->_window);
}

void Draw::clear(Vector4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/*
void Window::Draw::buffers(BufferBase<BUFFER_TYPE_VERTEX>* vertexBuffer, BufferBase<BUFFER_TYPE_INDEX>* indexBuffer, ShaderBase* shader) {

}
*/

void Draw::camera(Camera2D* camera) {
    _camera2d = camera;
}

void Draw::shader(ShaderBase* shader) {
    _topologyMode = shader->_info.topologyMode;
    if (shader->_info.cullMode != CULL_MODE_NONE) {
        glEnable(GL_CULL_FACE);
        glCullFace(shader->_info.cullMode);
    } else {
        glDisable(GL_CULL_FACE);
    }
    glPolygonMode(GL_FRONT_AND_BACK, shader->_info.renderMode);

    if (shader->_info.depthMode != DEPTH_MODE_NEVER) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(shader->_info.depthMode);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (shader->_info.alphaMode != ALPHA_MODE_NONE) {
        if (shader->_info.alphaMode == ALPHA_MODE_CLIP) {
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, shader->_info.alphaThreshold);
        } else {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    } else {
        glDisable(GL_BLEND);
    }

    glUseProgram(shader->_program);

    if (_camera2d != nullptr) {
        Matrix4x4 view = Matrix4x4::identity().translate(_camera2d->position).rotateZ(_camera2d->rotation);
        Matrix4x4 projection = _camera2d->getProjection();

        shader->setUniform("projection", projection);
        shader->setUniform("view", view);
    }
}

void Draw::mesh(MeshBase* mesh) {
    glBindVertexArray(mesh->_vao);
    glDrawElements(_topologyMode, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Draw::rect(Vector2 position, Vector2 size, float rotation, Vector4 color) {
    Matrix4x4 model = Matrix4x4::transform(position, Vector3(size.x, size.y, 1.0), rotation);

    shader(_defaultFill2d);
    _defaultFill2d->setUniform("tint", color);
    _defaultFill2d->setUniform("model", model);
    _defaultFill2d->setUniform("textured", false);

    mesh(_quad);
}

void Draw::line(Vector2 start, Vector2 end, Vector4 color) {
    _line->clear();
    _line->addVertex({start.x, start.y}, Vector3::one, Vector2::zero);
    _line->addVertex({end.x, end.y}, Vector3::one, Vector2::zero);
    _line->addIndex(0);
    _line->addIndex(1);
    _line->apply();

    shader(_defaultLine2d);
    _defaultLine2d->setUniform("tint", color);
    _defaultLine2d->setUniform("model", Matrix4x4::identity());
    _defaultLine2d->setUniform("textured", false);

    mesh(_line);
}

void Draw::image(Texture2D* texture, Vector2 position, Vector2 size, float rotation, Vector4 tint) {
    Matrix4x4 model = Matrix4x4::identity().scale(Vector3(size.x, -size.y, 1.0)).rotateZ(-rotation).translate(
            Vector3(position.x, position.y, 0));

    shader(_defaultFill2d);
    _defaultFill2d->setUniform("tint", tint);
    _defaultFill2d->setUniform("model", model);
    _defaultFill2d->setUniform("textured", true);
    _defaultFill2d->setUniform("tex", texture);

    mesh(_quad);
}