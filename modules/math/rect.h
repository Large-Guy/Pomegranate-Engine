#ifndef POMEGRANATEENGINE_RECT_H
#define POMEGRANATEENGINE_RECT_H

#include "vector2.h"

struct Rect {
    Vector2 position;
    Vector2 size;

    Rect();

    Rect(const Vector2 &position, const Vector2 &size);

    [[nodiscard]] Vector2 center() const;

    [[nodiscard]] Vector2 min() const;

    [[nodiscard]] Vector2 max() const;

    [[nodiscard]] bool contains(const Vector2 &point) const;

    [[nodiscard]] bool intersects(const Rect &rect) const;

    [[nodiscard]] Rect intersection(const Rect &rect) const;

    [[nodiscard]] Rect unionBetween(const Rect &rect) const;

    [[nodiscard]] Rect offset(const Vector2 &offset) const;

    [[nodiscard]] Rect scale(const Vector2 &scale) const;

    [[nodiscard]] Rect scale(float scale) const;

    [[nodiscard]] Rect lerp(const Rect &rect, float t) const;

    [[nodiscard]] Rect round() const;

    [[nodiscard]] Rect ceil() const;

    [[nodiscard]] Rect floor() const;

    [[nodiscard]] Rect abs() const;

    [[nodiscard]] Rect operator+(const Vector2 &v) const;

    [[nodiscard]] Rect operator-(const Vector2 &v) const;

    [[nodiscard]] Rect operator*(const Vector2 &v) const;

    [[nodiscard]] Rect operator/(const Vector2 &v) const;

    [[nodiscard]] Rect operator+(float v) const;

    [[nodiscard]] Rect operator-(float v) const;

    [[nodiscard]] Rect operator*(float v) const;

    [[nodiscard]] Rect operator/(float v) const;

    [[nodiscard]] bool operator==(const Rect &r) const;

    [[nodiscard]] bool operator!=(const Rect &r) const;

    void operator+=(const Vector2 &v);

    void operator-=(const Vector2 &v);

    void operator*=(const Vector2 &v);

    void operator/=(const Vector2 &v);

    void operator+=(float v);

    void operator-=(float v);

    void operator*=(float v);

    void operator/=(float v);

    void serialize(Archive &a) const;

    void deserialize(Archive &a);
};


#endif //POMEGRANATEENGINE_RECT_H
