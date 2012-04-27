/**
 * File:   Point.h
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 13, 2010, 11:42 AM
 */


#include "Point.h"
#include "main.h"

Point::Point() {
    x = y = z = 0.0;
}

Point::Point(double t_x, double t_y, double t_z) {
    x = t_x;
    y = t_y;
    z = t_z;
}

Point::Point(Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
}

Point::~Point() {
    x = y = z = 0.0;
}

Point& Point::operator =(const Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

Point Point::operator +(const Point& p) {
    *this += p;
    return *this;
}

Point Point::operator +(const float f) {
    *this += f;
    return *this;
}

Point Point::operator -(const Point& p) {
    *this -= p;
    return *this;
}

Point Point::operator -(const float f) {
    *this -= f;
    return *this;
}

Point Point::operator *(const float f) {
    *this *= f;
    return *this;
}

Point Point::operator /(const float f) {
    *this /= f;
    return *this;
}

void Point::operator +=(const Point& p) {
    x += p.x;
    y += p.y;
    z += p.z;
}

void Point::operator +=(const float f) {
    x += f;
    y += f;
    z += f;
}

void Point::operator -=(const Point& p) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
}

void Point::operator -=(const float f) {
    x -= f;
    y -= f;
    z -= f;
}

void Point::operator *=(const float f) {
    x *= f;
    y *= f;
    z *= f;
}

void Point::operator /=(const float f) {
    x /= f;
    y /= f;
    z /= f;
}

bool Point::operator ==(const Point& p) {
    return (x == p.x? true : false) && (y == p.y? true : false) && (z == p.z? true : false);
}

bool Point::operator !=(const Point& p) {
    return !((*this) == p);
}
