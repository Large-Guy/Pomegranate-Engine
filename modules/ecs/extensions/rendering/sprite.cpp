#include "sprite.h"

Sprite::Sprite() {
    texture = nullptr;
    normalMap = nullptr;
    normalStrength = 1.0f;
    zIndex = 0;
}

void Sprite::serialize(Archive& a) const {

}

void Sprite::deserialize(Archive& a) {

}