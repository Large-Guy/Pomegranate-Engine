#ifndef POMEGRANATEENGINE_TEXTURE2D_H
#define POMEGRANATEENGINE_TEXTURE2D_H

#include <core/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "enumerations.h"
#include "stb_image.h"
#include "surface2d.h"
#include "shader.h"

class Texture2D : Asset {
private:
    GLuint _id;
    GLuint _bind;
    Surface2D *_surface;
public:

    Texture2D();

    Texture2D(Surface2D *surface);

    ~Texture2D();

    void apply();

    Surface2D *getSurface();

    void setBindingSlot(uint slot);

    uint getID();

    uint getBind();

    friend class Window;
};

template<>
inline void ShaderBase::setUniform(const std::string &name, Texture2D *value) {
    GLint location = getLocation(name);
    Debug::WarnIf::isEqual(location, -1, "Uniform " + name + " not found");

    glUniform1i(location, value->getBind());
    glActiveTexture(GL_TEXTURE0 + value->getBind());
    glBindTexture(GL_TEXTURE_2D, value->getID());
}


#endif //POMEGRANATEENGINE_TEXTURE2D_H
