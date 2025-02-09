#ifndef POMEGRANATE_ENGINE_MATH_VECTOR4I_H
#define POMEGRANATE_ENGINE_MATH_VECTOR4I_H

#include <core/serializable.h>
#include <cmath>
#include <array>
#include "vector_types.h"

struct Vector4i {
    int x = 0, y = 0, z = 0, w = 0;

    Vector4i();

    Vector4i(int v);

    Vector4i(int x, int y, int z, int w = 0.0f);

    Vector4i operator+(const Vector4i& v) const;

    Vector4i operator-(const Vector4i& v) const;

    Vector4i operator*(const Vector4i& v) const;

    Vector4i operator/(const Vector4i& v) const;

    Vector4i operator*(float v) const;

    Vector4i operator/(float v) const;

    void operator+=(const Vector4i& v);

    void operator-=(const Vector4i& v);

    void operator*=(const Vector4i& v);

    void operator/=(const Vector4i& v);

    void operator*=(float v);

    void operator/=(float v);

    bool operator==(const Vector4i& v) const;

    operator Vector2() const;

    operator Vector2i() const;

    operator Vector3() const;

    operator Vector3i() const;

    operator Vector4() const;

    [[nodiscard]] float dot(const Vector4i& v) const;

    [[nodiscard]] float length() const;

    [[nodiscard]] Vector4i normalize() const;

    [[nodiscard]] Vector4i lerp(const Vector4i& v, float t) const;

    [[nodiscard]] Vector4i slerp(const Vector4i& v, float t) const;

    [[nodiscard]] Vector4i nlerp(const Vector4i& v, float t) const;

    [[nodiscard]] Vector4i cross(const Vector4i& v) const;

    [[nodiscard]] Vector4i reflect(const Vector4i& normal) const;

    [[nodiscard]] Vector4i refract(const Vector4i& normal, float eta) const;

    [[nodiscard]] Vector4i abs() const;

    void serialize(Archive& a) const;

    void deserialize(Archive& a);

    [[nodiscard]] std::array<int, 4> get() const;
};

template<>
struct std::hash<Vector4i> {
    size_t operator()(const Vector4i& v) const {
        return hash<int>()(v.x) ^ hash<int>()(v.y) ^ hash<int>()(v.z) ^ hash<int>()(v.w);
    }
};

#endif //POMEGRANATE_ENGINE_MATH_VECTOR4I_H
