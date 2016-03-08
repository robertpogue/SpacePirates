#pragma once
#include <cmath>

struct Point {
	float x, y;
	Point() : x(0), y(0) { }
	Point(float X, float Y) : x(X), y(Y) { }
	Point operator+(const Point& p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point& p) const {
		return Point(x - p.x, y - p.y);
	}
	float squareMagnitude() const {
		return x*x+y*y;
	}
   void rotateAboutOrigin(float radians) {
        float newX = x * cos(radians) - y * sin(radians);
        y = x * sin(radians) + y * cos(radians);
        x = newX;
    }
};