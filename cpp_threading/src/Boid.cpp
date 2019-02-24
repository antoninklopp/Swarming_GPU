#include <time.h>

#include "Boid.hpp"
#include <iostream>

Boid::Boid(Color color) {
	this->color = color;
}

bool Boid::operator==(Boid boid) {
	
	if (this->position == boid.position && this->velocity == boid.velocity)
		return true;
	else
		return false;
}

bool Boid::operator!=(Boid boid) {

	if (this->position != boid.position || this->velocity != boid.velocity)
		return true;
	else
		return false;
}

void Boid::computeNewVelocityAndPosition(vector<Vector2D> rules) {

	this->velocity += rules[0] + rules[1] + rules[2];
	this->position += this->velocity;
}

void Boid::boundPosition() {

	if (this->position.x < -1 + 0.02)
		this->velocity.x = .01f;

	if (this->position.y < -1 + 0.02)
		this->velocity.y = .01f;

	if (this->position.x > 1 - 0.02)
		this->velocity.x = -.01f;

	if (this->position.y > 1 - 0.02)
		this->velocity.y = -.01f;
}

void Boid::limitVelocity() {

	if (this->velocity.getNorm() > v_lim)
		this->velocity = this->velocity / this->velocity.getNorm() * v_lim;
}

void Boid::draw()
{
	float radians = (velocity.getAngle() + 270 * (pi / 180));
	float degrees = (radians * (180 / pi));

	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotatef(degrees, 0.0, 0.0, 1.0);
	glTranslatef(-position.x, -position.y, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(this->position.x, this->position.y);
	glVertex2f(this->position.x + 0.01f, this->position.y - 0.05f);
	glVertex2f(this->position.x - 0.01f, this->position.y - 0.05f);
	glEnd();

	glPopMatrix();
}