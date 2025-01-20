#ifndef POMEGRANATEENGINE_SPRITE_H
#define POMEGRANATEENGINE_SPRITE_H
#include <core/core.h>
#include <opengl/graphics.h>

class Sprite : Reflectable {
public:
    Texture2D* texture;
    Texture2D* normalMap;
    float normalStrength;

    int zIndex;

    Rect region;

    Sprite();

    void serialize(Archive& a) const override;
    void deserialize(Archive& a);
};


#endif //POMEGRANATEENGINE_SPRITE_H
