#ifndef POMEGRANATE_ENGINE_MATH_VECTOR2I_H
#define POMEGRANATE_ENGINE_MATH_VECTOR2I_H

#include <core/serializable.h>
#include <cmath>
#include <array>
#include "vector_types.h"

class Vector2i {
public:
    int x = 0, y = 0;

    Vector2i();

    Vector2i(int v);

    Vector2i(int x, int y);

    Vector2i operator+(const Vector2i& v) const;

    Vector2i operator-(const Vector2i& v) const;

    Vector2i operator*(const Vector2i& v) const;

    Vector2i operator/(const Vector2i& v) const;

    Vector2i operator*(int v) const;

    Vector2i operator/(int v) const;

    void operator+=(const Vector2i& v);

    void operator-=(const Vector2i& v);

    void operator*=(const Vector2i& v);

    void operator/=(const Vector2i& v);

    void operator*=(int v);

    void operator/=(int v);

    bool operator==(const Vector2i& v) const;

    operator Vector2() const;

    operator Vector3() const;

    operator Vector3i() const;

    operator Vector4() const;

    operator Vector4i();


    [[nodiscard]] int dot(const Vector2i& v) const;

    [[nodiscard]] int length() const;

    [[nodiscard]] Vector2i normalize() const;

    [[nodiscard]] Vector2i lerp(const Vector2i& v, float t) const;

    [[nodiscard]] Vector2i slerp(const Vector2i& v, float t) const;

    [[nodiscard]] Vector2i nlerp(const Vector2i& v, float t) const;

    [[nodiscard]] Vector2i cross(const Vector2i& v) const;

    [[nodiscard]] Vector2i reflect(const Vector2i& normal) const;

    [[nodiscard]] Vector2i refract(const Vector2i& normal, float eta) const;

    [[nodiscard]] Vector2i rotate(float angle) const;

    [[nodiscard]] Vector2i rotate(const Vector2i& pivot, float angle) const;

    [[nodiscard]] Vector2i abs() const;

    void serialize(Archive& a) const;

    void deserialize(Archive& a);

    [[nodiscard]] std::array<int, 2> get() const;
};

template<>
struct std::hash<Vector2i> {
    size_t operator()(const Vector2i& v) const {
        return hash<int>()(v.x) ^ hash<int>()(v.y);
    }
};

#endif //POMEGRANATE_ENGINE_MATH_VECTOR2I_H
