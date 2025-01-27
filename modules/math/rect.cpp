#include "rect.h"

Rect::Rect() {
    position = Vector2();
    size = Vector2();
}

Rect::Rect(const Vector2 &position, const Vector2 &size) {
    this->position = position;
    this->size = size;
}

Vector2 Rect::center() const {
    return position + size / 2.0f;
}

Vector2 Rect::min() const {
    return position;
}

Vector2 Rect::max() const {
    return position + size;
}

bool Rect::contains(const Vector2 &point) const {
    return point.x >= position.x && point.x <= position.x + size.x && point.y >= position.y &&
           point.y <= position.y + size.y;
}

bool Rect::intersects(const Rect &rect) const {
    return position.x < rect.position.x + rect.size.x && position.x + size.x > rect.position.x &&
           position.y < rect.position.y + rect.size.y && position.y + size.y > rect.position.y;
}

Rect Rect::intersection(const Rect &rect) const {
    Vector2 p1 = Vector2(std::max(position.x, rect.position.x), std::max(position.y, rect.position.y));
    Vector2 p2 = Vector2(std::min(position.x + size.x, rect.position.x + rect.size.x),
                         std::min(position.y + size.y, rect.position.y + rect.size.y));
    return Rect(p1, p2 - p1);
}

Rect Rect::unionBetween(const Rect &rect) const {
    Vector2 p1 = Vector2(std::min(position.x, rect.position.x), std::min(position.y, rect.position.y));
    Vector2 p2 = Vector2(std::max(position.x + size.x, rect.position.x + rect.size.x),
                         std::max(position.y + size.y, rect.position.y + rect.size.y));
    return Rect(p1, p2 - p1);
}

Rect Rect::offset(const Vector2 &offset) const {
    return Rect(position + offset, size);
}

Rect Rect::scale(const Vector2 &scale) const {
    return Rect(position, size * scale);
}

Rect Rect::scale(float scale) const {
    return Rect(position, size * scale);
}

Rect Rect::lerp(const Rect &rect, float t) const {
    return Rect(position.lerp(rect.position, t), size.lerp(rect.size, t));
}

Rect Rect::round() const {
    return Rect(position.round(), size.round());
}

Rect Rect::ceil() const {
    return Rect(position.ceil(), size.ceil());
}

Rect Rect::floor() const {
    return Rect(position.floor(), size.floor());
}

Rect Rect::abs() const {
    return Rect(position.abs(), size.abs());
}

Rect Rect::operator+(const Vector2 &v) const {
    return Rect(position + v, size);
}

Rect Rect::operator-(const Vector2 &v) const {
    return Rect(position - v, size);
}

Rect Rect::operator*(const Vector2 &v) const {
    return Rect(position * v, size * v);
}

Rect Rect::operator/(const Vector2 &v) const {
    return Rect(position / v, size / v);
}

Rect Rect::operator+(float v) const {
    return Rect(position + v, size);
}

Rect Rect::operator-(float v) const {
    return Rect(position - v, size);
}

Rect Rect::operator*(float v) const {
    return Rect(position * v, size * v);
}

Rect Rect::operator/(float v) const {
    return Rect(position / v, size / v);
}

bool Rect::operator==(const Rect &r) const {
    return position == r.position && size == r.size;
}

bool Rect::operator!=(const Rect &r) const {
    return position != r.position || size != r.size;
}

void Rect::operator+=(const Vector2 &v) {
    position += v;
}

void Rect::operator-=(const Vector2 &v) {
    position -= v;
}

void Rect::operator*=(const Vector2 &v) {
    position *= v;
    size *= v;
}

void Rect::operator/=(const Vector2 &v) {
    position /= v;
    size /= v;
}

void Rect::operator+=(float v) {
    position += v;
}

void Rect::operator-=(float v) {
    position -= v;
}

void Rect::operator*=(float v) {
    position *= v;
    size *= v;
}

void Rect::operator/=(float v) {
    position /= v;
    size /= v;
}

void Rect::serialize(Archive &a) const {
    a << position;
    a << size;
}

void Rect::deserialize(Archive &a) {
    a >> position;
    a >> size;
}