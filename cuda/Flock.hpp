#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "Boid.hpp"

#include <vector>
#include <thread>

#include <cuda.h>
#include <cuda_runtime.h>

#define NB_OF_BOIDS 100

class Flock {

public:

	static float *dev_old_velocity, *dev_new_velocity;

	static float *dev_cohesion, *dev_separation, *dev_alignment, *dev_position;

	static bool initialized; 

	Flock(Color color);

	std::vector<Boid> boids;

	Vector2D applyCohesionRule(Boid boid);
	Vector2D applySeparationRule(Boid boid);
	Vector2D applyAlignmentRule(Boid boid);
	
	void drawBoids();

	void moveBoidsToNewPositions();
};

#endif