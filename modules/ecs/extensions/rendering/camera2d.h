#ifndef POMEGRANATEENGINE_CAMERA2D_H
#define POMEGRANATEENGINE_CAMERA2D_H

#include <core/core.h>
#include <math/math.h>
#include <ecs/ecs.h>
#include <graphics/opengl/graphics.h>

class Camera2D : Reflectable {
private:
    static Entity _mainCamera;
public:
    float zoom;
    float near;
    float far;

    Camera2D();
    Camera2D(float zoom, float near, float far);

    static void setMain(Entity& entity);
    static Entity getMain();
    bool isMain() const;
    Matrix4x4 getProjectionMatrix() const;

    void serialize(Archive& a) const override;
    void deserialize(Archive& a) override;
};

#endif //POMEGRANATEENGINE_CAMERA2D_H
