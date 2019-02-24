#ifndef BOID_HPP
#define BOID_HPP

#include <vector>
#include "Vector2D.hpp"
#include "Common.hpp"

using namespace std;

class Boid {

private:

	Color color;

public:

	Boid(Color color);

	Vector2D velocity;
	Vector2D position;

	bool operator==(Boid boid);
	bool operator!=(Boid boid);

	void computeNewVelocityAndPosition(vector<Vector2D> rules);

	void boundPosition();
	void limitVelocity();

	void draw();
};

#endif