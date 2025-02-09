#ifndef POMEGRANATE_ENGINE_MATH_VEC2_H
#define POMEGRANATE_ENGINE_MATH_VEC2_H

#include <core/serializable.h>
#include <cmath>
#include <array>
#include "vector2i.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "vector4i.h"

struct Vector2 {
    static const Vector2 zero;
    static const Vector2 one;
    static const Vector2 up;
    static const Vector2 down;
    static const Vector2 left;
    static const Vector2 right;

    float x = 0, y = 0;

    Vector2();

    Vector2(float v);

    Vector2(float x, float y);

    Vector2 operator+(const Vector2& v) const;

    Vector2 operator-(const Vector2& v) const;

    Vector2 operator*(const Vector2& v) const;

    Vector2 operator/(const Vector2& v) const;

    Vector2 operator*(float v) const;

    Vector2 operator/(float v) const;

    void operator+=(const Vector2& v);

    void operator-=(const Vector2& v);

    void operator*=(const Vector2& v);

    void operator/=(const Vector2& v);

    void operator*=(float v);

    void operator/=(float v);

    bool operator==(const Vector2& v) const;

    operator Vector2i() const;

    operator Vector3() const;

    operator Vector3i() const;

    operator Vector4() const;

    operator Vector4i() const;

    [[nodiscard]] float dot(const Vector2& v) const;

    [[nodiscard]] float length() const;

    [[nodiscard]] Vector2 normalize() const;

    [[nodiscard]] Vector2 lerp(const Vector2& v, float t) const;

    [[nodiscard]] Vector2 slerp(const Vector2& v, float t) const;

    [[nodiscard]] Vector2 nlerp(const Vector2& v, float t) const;

    [[nodiscard]] Vector2 cross(const Vector2& v) const;

    [[nodiscard]] Vector2 reflect(const Vector2& normal) const;

    [[nodiscard]] Vector2 refract(const Vector2& normal, float eta) const;

    [[nodiscard]] Vector2 rotate(float angle) const;

    [[nodiscard]] Vector2 rotate(const Vector2& pivot, float angle) const;

    [[nodiscard]] Vector2 round() const;

    [[nodiscard]] Vector2 ceil() const;

    [[nodiscard]] Vector2 floor() const;

    [[nodiscard]] Vector2 abs() const;

    [[nodiscard]] float distanceTo(const Vector2& v) const;

    [[nodiscard]] Vector2 directionTo(const Vector2& v) const;

    void serialize(Archive& a) const;

    void deserialize(Archive& a);
};

template<>
struct std::hash<Vector2> {
    size_t operator()(const Vector2& v) const {
        return hash<float>()(v.x) ^ hash<float>()(v.y);
    }
};

#endif //POMEGRANATE_ENGINE_MATH_VEC2_H
