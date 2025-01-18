#ifndef POMEGRANATEENGINE_TEXTURE2D_H
#define POMEGRANATEENGINE_TEXTURE2D_H
#include <core/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "enumerations.h"
#include "stb_image.h"
#include "surface2d.h"

class Texture2D : Asset {
private:
    GLuint _id;
    Surface2D* _surface;
public:

    Texture2D();
    Texture2D(Surface2D* surface);
    ~Texture2D();

    void apply();

    Surface2D* getSurface();

    friend class Window;
};


#endif //POMEGRANATEENGINE_TEXTURE2D_H
