#ifndef POMEGRANATEENGINE_SHADER_H
#define POMEGRANATEENGINE_SHADER_H

#include "core.h"
#include <core/core.h>
#include "enumerations.h"
#include <math/math.h>

class ShaderBase {
protected:
    GLuint _program;
    RenderInfo _info;
public:

    GLint getLocation(const std::string& name) {
        glUseProgram(_program);

        GLint location = glGetUniformLocation(_program, name.c_str());
        return location;
    }

    template<typename T>
    void setUniform(const std::string& name, T value) {
        GLint location = getLocation(name);
        Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

        Debug::Log::error("Uniform type not supported");
    }

    std::vector<std::string> getShaderUniforms();

    ShaderBase() = default;

    virtual ~ShaderBase() = default;

    friend class Window;

    friend class Draw;
};

template<typename VertexType>
class Shader : public ShaderBase {
public:
    Shader() {
        _info = {.renderMode = RENDER_MODE_FILL, .cullMode = CULL_MODE_BACK};
    }

    Shader(const char* vertex, const char* fragment,
           RenderInfo info = {.renderMode = RENDER_MODE_FILL, .cullMode = CULL_MODE_BACK}) {
        _info = info;

        GLuint _vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertex, 1, &vertex, nullptr);
        glCompileShader(_vertex);

        //Check for errors
        GLint success;
        glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(_vertex, 512, nullptr, infoLog);
            Debug::Log::error("Vertex shader compilation failed:", infoLog);
        }

        GLuint _fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragment, 1, &fragment, nullptr);
        glCompileShader(_fragment);

        //Check for errors
        glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(_fragment, 512, nullptr, infoLog);
            Debug::Log::error("Fragment shader compilation failed:", infoLog);
        }

        _program = glCreateProgram();
        glAttachShader(_program, _vertex);
        glAttachShader(_program, _fragment);
        glLinkProgram(_program);

        //Check for errors
        glGetProgramiv(_program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(_program, 512, nullptr, infoLog);
            Debug::Log::error("Shader program linking failed:", infoLog);
        }

        glDeleteShader(_vertex);
        glDeleteShader(_fragment);
    }

    ~Shader() override {
        glDeleteProgram(_program);
    }

    friend Graphics;
    friend Window;
};

template<>
inline void ShaderBase::setUniform<int>(const std::string& name, int value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform1i(location, value);
}

template<>
inline void ShaderBase::setUniform<float>(const std::string& name, float value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform1f(location, value);
}

template<>
inline void ShaderBase::setUniform<bool>(const std::string& name, bool value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform1i(location, value);
}

template<>
inline void ShaderBase::setUniform<Vector2>(const std::string& name, Vector2 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform2f(location, value.x, value.y);
}

template<>
inline void ShaderBase::setUniform<Vector2i>(const std::string& name, Vector2i value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform2i(location, value.x, value.y);
}

template<>
inline void ShaderBase::setUniform<Vector3>(const std::string& name, Vector3 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform3f(location, value.x, value.y, value.z);
}

template<>
inline void ShaderBase::setUniform<Vector3i>(const std::string& name, Vector3i value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform3i(location, value.x, value.y, value.z);
}

template<>
inline void ShaderBase::setUniform<Vector4>(const std::string& name, Vector4 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform4f(location, value.x, value.y, value.z, value.w);
}

template<>
inline void ShaderBase::setUniform<Vector4i>(const std::string& name, Vector4i value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform4i(location, value.x, value.y, value.z, value.w);
}

template<>
inline void ShaderBase::setUniform<Matrix2x2>(const std::string& name, Matrix2x2 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniformMatrix2fv(location, 1, GL_FALSE, &value.x.x);
}

template<>
inline void ShaderBase::setUniform<Matrix3x3>(const std::string& name, Matrix3x3 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniformMatrix3fv(location, 1, GL_FALSE, &value.x.x);
}

template<>
inline void ShaderBase::setUniform<Matrix4x4>(const std::string& name, Matrix4x4 value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniformMatrix4fv(location, 1, GL_FALSE, &value.x.x);
}

#endif //POMEGRANATEENGINE_SHADER_H
