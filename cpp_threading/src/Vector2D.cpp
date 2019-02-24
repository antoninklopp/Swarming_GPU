#include "Vector2D.hpp"

// Constructors

Vector2D::Vector2D() {
  
  this->x = 0;
  this->y = 0;
}

Vector2D::Vector2D(float x, float y) {
  
  this->x = x;
  this->y = y;
}

// Vector2D <-> Vector2D Incrementations

void Vector2D::operator+=(const Vector2D &v) {
  
  this->x += v.x;
  this->y += v.y;
}

void Vector2D::operator-=(const Vector2D &v) {

  this->x -= v.x;
  this->y -= v.y;
}

// Vector2D <-> Float Incrementations

void Vector2D::operator*=(const float f) {

  this->x *= f;
  this->y *= f;
}

void Vector2D::operator/=(const float f) {

  this->x /= f;
  this->y /= f;
}

// Vector2D <-> Vector2D Operations

Vector2D Vector2D::operator+(const Vector2D &v) const {
  
  return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v) const {

  return Vector2D(this->x - v.x, this->y - v.y);
}

// Vector2D <-> Float Operations

Vector2D Vector2D::operator*(const float f) const {

  return Vector2D(this->x * f, this->y * f);
}

Vector2D Vector2D::operator/(const float f) const {

  return Vector2D(this->x / f, this->y / f);
}

// Other operations

bool Vector2D::operator==(const Vector2D &v) {

	return (this->x == v.x && this->x == v.y);
}

bool Vector2D::operator!=(const Vector2D &v) {

	return (this->x != v.x || this->x != v.y);
}

float Vector2D::getDistance(const Vector2D &v) {

	return (sqrtf(pow(this->x - v.x, 2.0) + pow(this->y - v.y, 2.0)));
}

float Vector2D::getNorm() {

	return (sqrtf(pow(this->x, 2.0) + pow(this->y, 2.0)));
}

float Vector2D::getAngle() {

	return atan2f(this->y, this->x);
}
