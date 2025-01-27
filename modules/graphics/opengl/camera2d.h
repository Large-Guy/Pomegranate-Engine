#ifndef POMEGRANATEENGINE_CAMERA2D_H
#define POMEGRANATEENGINE_CAMERA2D_H

#include <math/math.h>

class Camera2D {
public:
    Vector2 position;
    Vector2 size;
    float rotation;
    float zoom;

    Camera2D(Vector2 position, Vector2 size, float rotation, float zoom);

    Matrix4x4 getProjection();

    Matrix4x4 getView();

    void serialize(Archive& archive);

    void deserialize(Archive& archive);
};


#endif //POMEGRANATEENGINE_CAMERA2D_H
