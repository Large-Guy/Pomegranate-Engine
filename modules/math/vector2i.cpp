#include "vector2i.h"
#include "vector3.h"
#include "vector2.h"
#include "vector3i.h"
#include "vector4.h"
#include "vector4i.h"

Vector2i::Vector2i() {
    x = 0;
    y = 0;
}

Vector2i::Vector2i(int v) {
    x = v;
    y = v;
}

Vector2i::Vector2i(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2i Vector2i::operator+(const Vector2i& v) const {
    return Vector2i(x + v.x, y + v.y);
}

Vector2i Vector2i::operator-(const Vector2i& v) const {
    return Vector2i(x - v.x, y - v.y);
}

Vector2i Vector2i::operator*(const Vector2i& v) const {
    return Vector2i(x * v.x, y * v.y);
}

Vector2i Vector2i::operator/(const Vector2i& v) const {
    return Vector2i(x / v.x, y / v.y);
}

Vector2i Vector2i::operator*(int v) const {
    return Vector2i(x * v, y * v);
}

Vector2i Vector2i::operator/(int v) const {
    return Vector2i(x / v, y / v);
}

void Vector2i::operator+=(const Vector2i& v) {
    x += v.x;
    y += v.y;
}

void Vector2i::operator-=(const Vector2i& v) {
    x -= v.x;
    y -= v.y;
}

void Vector2i::operator*=(const Vector2i& v) {
    x *= v.x;
    y *= v.y;
}

void Vector2i::operator/=(const Vector2i& v) {
    x /= v.x;
    y /= v.y;
}

void Vector2i::operator*=(int v) {
    x *= v;
    y *= v;
}

void Vector2i::operator/=(int v) {
    x /= v;
    y /= v;
}

bool Vector2i::operator==(const Vector2i& v) const {
    return x == v.x && y == v.y;
}

int Vector2i::dot(const Vector2i& v) const {
    return x * v.x + y * v.y;
}

int Vector2i::length() const {
    return sqrtf(x * x + y * y);
}

Vector2i Vector2i::normalize() const {
    int l = length();
    return Vector2i(x / l, y / l);
}

Vector2i Vector2i::lerp(const Vector2i& v, float t) const {
    return *this + (v - *this) * t;
}

Vector2i Vector2i::slerp(const Vector2i& v, float t) const {
    int dot = normalize().dot(v.normalize());
    //Clamp
    dot = fmaxf(-1.0f, fminf(1.0f, dot));
    int theta = acosf(dot) * t;
    Vector2i relative = (v - *this * dot).normalize();
    return *this * cosf(theta) + relative * sinf(theta);
}

Vector2i Vector2i::nlerp(const Vector2i& v, float t) const {
    return lerp(v, t).normalize();
}

Vector2i Vector2i::cross(const Vector2i& v) const {
    return Vector2i(y * v.x - x * v.y, x * v.y - y * v.x);
}

Vector2i Vector2i::reflect(const Vector2i& normal) const {
    return *this - normal * 2 * dot(normal);
}

Vector2i Vector2i::refract(const Vector2i& normal, float eta) const {
    int dot = this->dot(normal);
    int k = 1.0f - eta * eta * (1.0f - dot * dot);
    if (k < 0.0f) {
        return Vector2i(0.0f);
    }
    return *this * eta - normal * (eta * dot + sqrtf(k));
}

Vector2i Vector2i::rotate(float angle) const {
    int s = sinf(angle);
    int c = cosf(angle);
    return Vector2i(x * c - y * s, x * s + y * c);
}

Vector2i Vector2i::rotate(const Vector2i& pivot, float angle) const {
    return (*this - pivot).rotate(angle) + pivot;
}

Vector2i Vector2i::abs() const {
    return Vector2i(std::abs(x), std::abs(y));
}

void Vector2i::serialize(Archive& a) const {
    a << x << y;
}

void Vector2i::deserialize(Archive& a) {
    a >> x >> y;
}

std::array<int, 2> Vector2i::get() const {
    return {x, y};
}

Vector2i::operator Vector2() const {
    return {(float) x, (float) y};
}

Vector2i::operator Vector3() const {
    return {(float) x, (float) y, 0.0f};
}

Vector2i::operator Vector3i() const {
    return {x, y, 0};
}

Vector2i::operator Vector4() const {
    return {(float) x, (float) y, 0.0f, 0.0f};
}

Vector2i::operator Vector4i() {
    return {x, y, 0, 0};
}
