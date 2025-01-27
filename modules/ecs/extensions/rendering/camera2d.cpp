#include "camera2d.h"

Entity Camera2D::_mainCamera = nullptr;

Camera2D::Camera2D() {
    zoom = 1.0f;
    near = 0.1f;
    far = 100.0f;
    property("zoom", &this->zoom);
    property("near", &this->near);
    property("far", &this->far);
}

Camera2D::Camera2D(float zoom, float near, float far) {
    this->zoom = zoom;
    this->near = near;
    this->far = far;
    property("zoom", &this->zoom);
    property("near", &this->near);
    property("far", &this->far);
}

Matrix4x4 Camera2D::getProjectionMatrix() const {
    Vector2i size = Window::getCurrent()->getSize();
    return Matrix4x4::orthographic(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 100.0f);
}

void Camera2D::setMain(Entity& entity) {
    _mainCamera = entity;
}

Entity Camera2D::getMain() {
    return _mainCamera;
}

bool Camera2D::isMain() const {
    return _mainCamera.get<Camera2D>() == this;
}

void Camera2D::serialize(Archive& a) const {
    a << this->zoom;
    a << this->near;
    a << this->far;
}

void Camera2D::deserialize(Archive& a) {
    a >> this->zoom;
    a >> this->near;
    a >> this->far;
}