#include "shader.h"

std::vector<std::string> ShaderBase::getShaderUniforms() {
    std::vector<std::string> uniformNames;

    // Get the number of active uniforms
    GLint uniformCount = 0;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &uniformCount);

    // Get the maximum length of uniform names
    GLint maxNameLength = 0;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

    // Allocate a buffer to store uniform names
    std::vector<GLchar> nameBuffer(maxNameLength);

    // Iterate through each active uniform
    for (GLint i = 0; i < uniformCount; ++i) {
        GLsizei nameLength = 0;
        GLint size = 0;
        GLenum type = 0;

        // Query uniform information
        glGetActiveUniform(_program, i, maxNameLength, &nameLength, &size, &type, nameBuffer.data());

        // Add the uniform name to the list
        std::string uniformName(nameBuffer.data(), nameLength);
        uniformNames.push_back(uniformName);
    }

    return uniformNames;
}