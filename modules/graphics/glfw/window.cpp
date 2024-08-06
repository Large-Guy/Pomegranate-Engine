#include "window.h"

#include <utility>

Window::Window() {
    _window = nullptr;
}

Window::~Window() {
    if (_open) {
        close();
    }
}

void Window::setSize(int width, int height) {
    this->_width = width;
    this->_height = height;
}

void Window::setTitle(const char* title) {
    this->_title = title;
}

void Window::open() {
    _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
    }
    _open = true;

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
    }
    if(!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    draw._window = _window;
    draw.init();
}

void Window::close() {
    glfwDestroyWindow(_window);
    _open = false;
}

bool Window::isOpen() const {
    return _open;
}

int Window::getWidth() const {
    return _width;
}

int Window::getHeight() const {
    return _height;
}

void Window::pollEvents() {
    glfwPollEvents();
    //Close window if close button is pressed
    if (glfwWindowShouldClose(_window)) {
        close();
    }
}

GLFWwindow *Window::getGLFWwindow() const {
    return _window;
}

void Window::Draw::begin() {
    glfwMakeContextCurrent(_window);
    _color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::Draw::end() {
    glfwSwapBuffers(_window);
}

void Window::Draw::clear() const {
    glClearColor(_color.x,_color.y,_color.z,_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Window::Draw::drawTexture(Texture2D* texture, Vector2 position, Vector2 size, float rotation) {
    texture->bind(0);
    Matrix3x3 modelMatrix = Matrix3x3::createTransform(position, size, rotation);

    _currentShader->use();
    _currentShader->set("SCREEN_RESOLUTION", Vector2((float)Graphics::getViewportWidth(), (float)Graphics::getViewportHeight()));
    _currentShader->set("TEXTURE", texture);
    _currentShader->set("MODEL_MATRIX", modelMatrix);
    _currentShader->set("Z_INDEX", _z_index);
    _rect->draw();
}

void Window::Draw::setColor(Vector4 color) {
    _color = std::move(color);
}

void Window::Draw::setColor(const Vector3& color, float a) {
    _color = Vector4(color.x, color.y, color.z, a);
}

void Window::Draw::setShader(Shader *shader) {
    if(shader == nullptr)
    {
        _currentShader = _shader;
        return;
    }
    _currentShader = shader;
}

void Window::Draw::setZIndex(float z_index) {
    _z_index = z_index;
}

void Window::Draw::init() {
    _color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    _rect = new Model2D();
    //Create a rectangle model
    _rect->addVertex({
                            {-1.0,-1.0},
                            {1.0},
                            {0.0,0.0}
                    });
    _rect->addVertex({
                            {-1.0,1.0},
                            {1.0},
                            {0.0,1.0}
    });
    _rect->addVertex({
                            {1.0,1.0},
                            {1.0},
                            {1.0,1.0}
    });
    _rect->addVertex({
                            {1.0,-1.0},
                            {1.0},
                            {1.0,0.0}
    });

    _rect->addIndex(2);
    _rect->addIndex(1);
    _rect->addIndex(0);

    _rect->addIndex(3);
    _rect->addIndex(2);
    _rect->addIndex(0);

    _rect->regenerateBuffers();

    //Create a tileMapShader program
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    //Load from file
    _shader = new Shader("assets/shaders/default2d/vertex.glsl", "assets/shaders/default2d/fragment.glsl");
    _currentShader = _shader;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Shader *Window::Draw::getShader() const {
    return _currentShader;
}

