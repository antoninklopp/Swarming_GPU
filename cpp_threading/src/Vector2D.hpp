#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>
#include <iostream>

class Vector2D {

public:

	float x;
	float y;

	// Constructors

	Vector2D();
	Vector2D(float x, float y);

	// Vector2D <-> Vector2D Incrementations

	void operator+=(const Vector2D &v);
	void operator-=(const Vector2D &v);

	// Vector2D <-> Float Incrementations

	void operator*=(const float f);
	void operator/=(const float f);

	// Vector2D <-> Vector2D Operations

	Vector2D operator+(const Vector2D &v) const;
	Vector2D operator-(const Vector2D &v) const;

	// Vector2D <-> Float Operations

	Vector2D operator*(const float f) const;
	Vector2D operator/(const float f) const;

	// Other operations

	bool operator==(const Vector2D &v);
	bool operator!=(const Vector2D &v);

	float getDistance(const Vector2D &v);
	float getNorm();
	float getAngle();
};


#endif
