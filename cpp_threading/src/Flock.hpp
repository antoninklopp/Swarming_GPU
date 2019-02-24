#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "Boid.hpp"

#include <vector>
#include <thread>

class Flock {

public:

	Flock(Color color);

	std::vector<Boid> boids;

	Vector2D applyCohesionRule(Boid boid);
	Vector2D applySeparationRule(Boid boid);
	Vector2D applyAlignmentRule(Boid boid);
	
	void drawBoids();

	void moveBoidsToNewPositions();
};

#endif