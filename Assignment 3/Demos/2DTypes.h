#pragma once

#include "vector.h"
#include <ostream>

/* Type representing a point in 2D space. */
struct Point {
    int x, y;
};

/* Type representing a rectangle in 2D space. The rectangle is defined by
 * the (x, y) coordinate of its upper-left corner, plus a width and height.
 * Rectangles are such that the top and left sides of the rectangle are
 * included within the rectangle, while the bottom and right sides are
 * not.
 */
struct Rectangle {
    int x = 0, y = 0, width = 0, height = 0;
};

/* Type representing a vector in 2D space. You are not expected to use
 * this type in the course of solving this assignment, but you may find
 * it useful for doing more advanced graphics. (We use it internally in
 * a few places.)
 */
struct Vector2D {
    int dx = 0, dy = 0;
};

/* Helper functions for working with these types in SimpleTest. */
bool operator== (const Point& one, const Point& two);
bool operator== (const Rectangle& one, const Rectangle& two);
bool operator== (const Vector2D& one, const Vector2D& two);
std::ostream& operator<< (std::ostream& out, const Point& pt);
std::ostream& operator<< (std::ostream& out, const Rectangle& rect);
std::ostream& operator<< (std::ostream& out, const Vector2D& v);

/* Operations on Points and Vector2Ds. This allows us to write out
 * nice mathematical expressions like p + (v1 - v0) or p2 + (p1 - p0)
 * and have everything work the way it mathematically is expected to.
 */
Vector2D operator- (const Point& p1, const Point& p2);

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);
Vector2D operator- (const Vector2D& v1, const Vector2D& v2);

Point operator+ (const Point& p, const Vector2D& v);
Point operator+ (const Vector2D& v, const Point& p);
Point operator- (const Point& p, const Vector2D& v);

Point& operator+= (Point& p, const Vector2D& v);
Point& operator-= (Point& p, const Vector2D& v);

Vector2D operator- (const Vector2D& v);

Vector2D& operator+= (Vector2D& v1, const Vector2D& v2);
Vector2D& operator-= (Vector2D& v1, const Vector2D& v2);

Vector2D operator* (const Vector2D& v, double scalar);
Vector2D operator* (double scalar, const Vector2D& v);
Vector2D operator/ (const Vector2D& v, double scalar);

Vector2D& operator*= (Vector2D& v, double scalar);
Vector2D& operator/= (Vector2D& v, double scalar);
