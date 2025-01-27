#ifndef POMEGRANATEENGINE_SURFACE_H
#define POMEGRANATEENGINE_SURFACE_H

#include <core/core.h>
#include "enumerations.h"
#include <string>

class Surface2D : Asset {
private:
    int _width;
    int _height;
    int _channels;
    TextureFormat _format;
    unsigned char* _data;
    TextureFilter _filter;
    TextureWrap _wrap;
public:

    Surface2D();

    Surface2D(int width, int height, TextureFormat format, TextureFilter filter, TextureWrap wrap);

    Surface2D(const std::string& path, const std::string& name);

    ~Surface2D();

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

    friend class Texture2D;
};

#endif //POMEGRANATEENGINE_SURFACE_H
