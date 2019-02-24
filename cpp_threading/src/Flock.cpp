#include "Flock.hpp"
#include "Common.hpp"
using namespace std;

Flock::Flock(Color color) {

	int nb_of_boids = 10;

	for (int i = 0; i < nb_of_boids; i++) {

		Boid boid(color);

		float x = rand() / (float)RAND_MAX; /* [0, 1.0] */
		x = x * (1 - (-1)) - 1;

		float y = rand() / (float)RAND_MAX; /* [0, 1.0] */
		y = y * (1 - (-1)) - 1;

		boid.position = Vector2D(x, y);
		boids.push_back(boid);
	}
}

Vector2D Flock::applyCohesionRule(Boid boid) {

	Vector2D center_of_mass;
	Vector2D cohesion_vector;

	for (int i = 0; i < this->boids.size(); i++)
		if (this->boids[i] != boid)
			center_of_mass += this->boids[i].position;
			 
	center_of_mass /= this->boids.size() - 1;

	cohesion_vector = (center_of_mass - boid.position) / cohesion_parameter;
	return cohesion_vector;
}

Vector2D Flock::applySeparationRule(Boid boid) {

	Vector2D separation_vector;

	for (int i = 0; i < this->boids.size(); i++)
		if (this->boids[i] != boid)
			if (this->boids[i].position.getDistance(boid.position) < separation_distance)
				separation_vector -= (this->boids[i].position - boid.position) / separation_parameter;

	return separation_vector;
}

Vector2D Flock::applyAlignmentRule(Boid boid) {

	Vector2D perceived_velocity;
	Vector2D alignment_vector;

	for (int i = 0; i < this->boids.size(); i++)
		if (this->boids[i] != boid)
			perceived_velocity += this->boids[i].velocity;

	perceived_velocity /= this->boids.size() - 1;

	alignment_vector = (perceived_velocity - boid.velocity) / alignment_parameter;
	return alignment_vector;
}

void Flock::drawBoids() {

	for (int i = 0; i < this->boids.size(); i++) {

		this->boids[i].draw();
	}
}

void Flock::moveBoidsToNewPositions() {

	vector< vector<Vector2D> > boids_rule_vectors;

	for (int i = 0; i < this->boids.size(); i++) {

		vector<Vector2D> boid_i_rule_vectors;

		Vector2D v1 = applyCohesionRule(this->boids[i]);
		Vector2D v2 = applySeparationRule(this->boids[i]);
		Vector2D v3 = applyAlignmentRule(this->boids[i]);

		boid_i_rule_vectors.push_back(v1);
		boid_i_rule_vectors.push_back(v2);
		boid_i_rule_vectors.push_back(v3);


		boids_rule_vectors.push_back(boid_i_rule_vectors);
	}

	vector<std::thread> boids_threads;

	for (int i = 0; i < this->boids.size(); i++) {

		boids_threads.push_back(thread(&Boid::computeNewVelocityAndPosition, &this->boids[i], boids_rule_vectors[i]));
	}

	for (int i = 0; i < this->boids.size(); i++) {

		boids_threads[i].join();
	}

	for (int i = 0; i < this->boids.size(); i++) {

		this->boids[i].boundPosition();
		this->boids[i].limitVelocity();
	}
}
