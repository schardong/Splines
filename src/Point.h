/**
 * File:   Point.h
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 13, 2010, 11:42 AM
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point {
public:
    double x, y, z;

    Point();
    Point(double t_x, double t_y, double t_z);
    Point(Point& p);
    ~Point();
    Point& operator =(const Point& p);
    Point operator +(const Point& p);
    Point operator +(const float f);
    Point operator -(const Point& p);
    Point operator -(const float f);
    Point operator *(const float f);
    Point operator /(const float f);
    void operator +=(const Point& p);
    void operator +=(const float f);
    void operator -=(const Point& p);
    void operator -=(const float f);
    void operator *=(const float f);
    void operator /=(const float f);
    bool operator ==(const Point& p);
    bool operator !=(const Point& p);
    inline friend std::ostream& operator <<(std::ostream& t_stream, const Point& p) {
        t_stream << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return t_stream;
    }
};

#endif /* __POINT_H__ */

