#ifndef POMEGRANATEENGINE_TEXTURE2D_H
#define POMEGRANATEENGINE_TEXTURE2D_H
#include <core/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "enumerations.h"
#include "stb_image.h"

class Texture2D : Asset {
private:
    GLuint _id;
    int _width;
    int _height;
    int _channels;
    TextureFormat _format;
    unsigned char* _data;
    TextureFilter _filter;
    TextureWrap _wrap;
public:

    Texture2D();
    Texture2D(int width, int height, TextureFormat format, TextureFilter filter, TextureWrap wrap);
    Texture2D(const std::string& path, const std::string& name);
    ~Texture2D();

    void apply();

    int getWidth();
    int getHeight();
    int getChannels();
    TextureFormat getFormat();
    unsigned char* getData();
    TextureFilter getFilter();
    TextureWrap getWrap();

    void setFilter(TextureFilter filter);
    void setWrap(TextureWrap wrap);

    friend class Window;
};


#endif //POMEGRANATEENGINE_TEXTURE2D_H
