#include "vector4i.h"
#include "vector2.h"
#include "vector3.h"
#include "vector2i.h"
#include "vector3i.h"
#include "vector4.h"

Vector4i::Vector4i() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4i::Vector4i(int v) {
    x = v;
    y = v;
    z = v;
    w = v;
}

Vector4i::Vector4i(int x, int y, int z, int w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4i Vector4i::operator+(const Vector4i& v) const {
    return Vector4i(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4i Vector4i::operator-(const Vector4i& v) const {
    return Vector4i(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4i Vector4i::operator*(const Vector4i& v) const {
    return Vector4i(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vector4i Vector4i::operator/(const Vector4i& v) const {
    return Vector4i(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4i Vector4i::operator*(float v) const {
    return Vector4i(x * v, y * v, z * v, w * v);
}

Vector4i Vector4i::operator/(float v) const {
    return Vector4i(x / v, y / v, z / v, w / v);
}

void Vector4i::operator+=(const Vector4i& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void Vector4i::operator-=(const Vector4i& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void Vector4i::operator*=(const Vector4i& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
}

void Vector4i::operator/=(const Vector4i& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
}

void Vector4i::operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
}

void Vector4i::operator/=(float v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;
}

bool Vector4i::operator==(const Vector4i& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

float Vector4i::dot(const Vector4i& v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

float Vector4i::length() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

Vector4i Vector4i::normalize() const {
    float len = length();
    return Vector4i(x / len, y / len, z / len, w / len);
}

Vector4i Vector4i::lerp(const Vector4i& v, float t) const {
    return *this + (v - *this) * t;
}

Vector4i Vector4i::slerp(const Vector4i& v, float t) const {
    float dot = normalize().dot(v.normalize());
    dot = fmaxf(fminf(dot, 1), -1);
    float theta = acosf(dot) * t;
    Vector4i relative = (v - *this * dot).normalize();
    return *this * cosf(theta) + relative * sinf(theta);
}

Vector4i Vector4i::nlerp(const Vector4i& v, float t) const {
    return lerp(v, t).normalize();
}

Vector4i Vector4i::cross(const Vector4i& v) const {
    return Vector4i(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0);
}

Vector4i Vector4i::reflect(const Vector4i& normal) const {
    return *this - normal * 2 * dot(normal);
}

Vector4i Vector4i::refract(const Vector4i& normal, float eta) const {
    float dot = this->dot(normal);
    float k = 1.0f - eta * eta * (1.0f - dot * dot);
    if (k < 0.0f)
        return Vector4i(0);
    else
        return *this * eta - normal * (eta * dot + sqrtf(k));
}

Vector4i Vector4i::abs() const {
    return Vector4i(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
}

void Vector4i::serialize(Archive& a) const {
    a << x << y << z << w;
}

void Vector4i::deserialize(Archive& a) {
    a >> x >> y >> z >> w;
}

std::array<int, 4> Vector4i::get() const {
    return {x, y, z, w};
}

Vector4i::operator Vector2() const {
    return {(float) x, (float) y};
}

Vector4i::operator Vector2i() const {
    return {x, y};
}

Vector4i::operator Vector3() const {
    return {(float) x, (float) y, (float) z};
}

Vector4i::operator Vector3i() const {
    return {x, y, z};
}

Vector4i::operator Vector4() const {
    return {(float) x, (float) y, (float) z, (float) w};
}