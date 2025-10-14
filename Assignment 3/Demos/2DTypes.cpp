#include "2DTypes.h"
#include "GUI/TextUtils.h"
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& out, const Rectangle& rect) {
    return out << format("{ %s, %s, %s, %s }", rect.x, rect.y, rect.width, rect.height);
}

bool operator== (const Rectangle& r1, const Rectangle& r2) {
    return r1.x      == r2.x &&
           r1.y      == r2.y &&
           r1.width  == r2.width &&
           r1.height == r2.height;
}

bool operator== (const Point& p0, const Point& p1) {
    return p0.x == p1.x && p0.y == p1.y;
}

ostream& operator<< (ostream& out, const Point& pt) {
    return out << format("{ %s, %s }", pt.x, pt.y);
}

Vector2D operator- (const Point& p1, const Point& p2) {
    return { p1.x - p2.x, p1.y - p2.y };
}

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2) {
    return { v1.dx + v2.dx, v1.dy + v2.dy };
}
Vector2D operator- (const Vector2D& v1, const Vector2D& v2) {
    return v1 + (-v2);
}

Point operator+ (const Point& p, const Vector2D& v) {
    return { p.x + v.dx, p.y + v.dy };
}
Point operator+ (const Vector2D& v, const Point& p) {
    return p + v;
}
Point operator- (const Point& p, const Vector2D& v) {
    return p + (-v);
}

Point& operator+= (Point& p, const Vector2D& v) {
    p.x += v.dx;
    p.y += v.dy;
    return p;
}
Point& operator-= (Point& p, const Vector2D& v) {
    p.x -= v.dx;
    p.y -= v.dy;
    return p;
}

Vector2D operator- (const Vector2D& v) {
    return { -v.dx, -v.dy };
}

Vector2D& operator+= (Vector2D& v1, const Vector2D& v2) {
    v1.dx += v2.dx;
    v1.dy += v2.dy;
    return v1;
}

Vector2D& operator-= (Vector2D& v1, const Vector2D& v2) {
    v1.dx -= v2.dx;
    v1.dy -= v2.dy;
    return v1;
}

Vector2D operator* (const Vector2D& v, double scalar) {
    return { int(v.dx * scalar), int(v.dy * scalar) };
}

Vector2D operator* (double scalar, const Vector2D& v) {
    return v * scalar;
}

Vector2D operator/ (const Vector2D& v, double scalar) {
    return v * (1 / scalar);
}

Vector2D& operator*= (Vector2D& v, double scalar) {
    v.dx *= scalar;
    v.dy *= scalar;
    return v;
}

Vector2D& operator/= (Vector2D& v, double scalar) {
    return v *= (1 / scalar);
}
