#include "texture2d.h"

Texture2D::Texture2D() {
    _id = 0;
    _surface = nullptr;
}

Texture2D::Texture2D(Surface2D* surface) {
    _id = 0;
    _surface = surface;
    apply();
}

Texture2D::~Texture2D() {
    if (_id != 0) {
        glDeleteTextures(1, &_id);
    }
}

void Texture2D::apply() {
    if (_id == 0) {
        glGenTextures(1, &_id);
    }

    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _surface->getFormat(), _surface->getWidth(), _surface->getHeight(), 0,
                 _surface->getFormat(), GL_UNSIGNED_BYTE, _surface->getData());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    switch (_surface->getFilter()) {
        case TEXTURE_FILTER_NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case TEXTURE_FILTER_LINEAR:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }

    switch (_surface->getWrap()) {
        case TEXTURE_WRAP_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case TEXTURE_WRAP_CLAMP:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case TEXTURE_WRAP_MIRRORED_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
    }
}

Surface2D* Texture2D::getSurface() {
    return _surface;
}

void Texture2D::setBindingSlot(uint slot) {
    _bind = slot;
}

uint Texture2D::getID() {
    return _id;
}

uint Texture2D::getBind() {
    return _bind;
}