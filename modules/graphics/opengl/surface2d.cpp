#include "surface2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Surface2D::Surface2D() {
    _id = 0;
    _width = 0;
    _height = 0;
    _format = TEXTURE_FORMAT_RGBA;
    _data = nullptr;
}

Surface2D::Surface2D(int width, int height, TextureFormat format, TextureFilter filter, TextureWrap wrap) {
    _id = 0;
    _width = width;
    _height = height;
    _format = format;
    _filter = filter;
    _wrap = wrap;

    int channels = 0;
    switch (format) {
        case TEXTURE_FORMAT_R:
            channels = 1;
            break;
        case TEXTURE_FORMAT_RG:
            channels = 2;
            break;
        case TEXTURE_FORMAT_RGB:
            channels = 3;
            break;
        case TEXTURE_FORMAT_RGBA:
            channels = 4;
            break;
        case TEXTURE_FORMAT_DEPTH:
            channels = 1;
            break;
    }

    _data = new unsigned char[width * height * channels];
}

Surface2D::Surface2D(const std::string& path, const std::string& name) : Asset(path, name){
    _id = 0;
    _width = 0;
    _height = 0;
    _format = TEXTURE_FORMAT_RGBA;
    _data = nullptr;
    _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    if (_data == nullptr) {
        Debug::Log::error("Failed to load texture: " + path);
    }
}

Surface2D::~Surface2D() {
    if (_id != 0) {
        glDeleteTextures(1, &_id);
    }

    if (_data != nullptr) {
        delete[] _data;
    }
}

int Surface2D::getWidth() {
    return _width;
}

int Surface2D::getHeight() {
    return _height;
}

int Surface2D::getChannels() {
    return _channels;
}

TextureFormat Surface2D::getFormat() {
    return _format;
}

unsigned char* Surface2D::getData() {
    return _data;
}

TextureFilter Surface2D::getFilter() {
    return _filter;
}

TextureWrap Surface2D::getWrap() {
    return _wrap;
}

void Surface2D::setFilter(TextureFilter filter) {
    _filter = filter;
}

void Surface2D::setWrap(TextureWrap wrap) {
    _wrap = wrap;
}