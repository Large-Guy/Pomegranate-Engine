#include "camera2d.h"

Camera2D::Camera2D(Vector2 position, Vector2 size, float rotation, float zoom) {
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->zoom = zoom;
}

Matrix4x4 Camera2D::getProjection() {
    return Matrix4x4::orthographic(-size.x / 2, size.x / 2, -size.y / 2, size.y / 2, -1.0f, 1.0f);
}

Matrix4x4 Camera2D::getView() {
    return Matrix4x4::identity().translate(position).rotateZ(rotation);
}

void Camera2D::serialize(Archive& archive) {
    archive << position << size << rotation << zoom;
}

void Camera2D::deserialize(Archive& archive) {
    archive >> position >> size >> rotation >> zoom;
}