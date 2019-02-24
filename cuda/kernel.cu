#include <cuda.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <stdio.h>
#include <iostream>

#define NB_OF_BOIDS 1000
#define NB_BLOCKS 64
#define VISION_DISTANCE 2
#define COHESION_PARAMETER 50
#define SEPARATION_PARAMETER 5
#define ALIGNMENT_PARAMETER 50
#define SEPARATION_DISTANCE 0.05

__device__ 
float get_distance(float &position1x, float& position1y, float position2x, float position2y){
	return sqrt((position1x - position2x) * (position1x - position2x) + 
		(position1y - position2y) * (position1y - position2y));  
}

__device__
void applyRules(float* boid_positions, float* velocity, float *new_velocity, int this_index, int size) {

	float2 center_of_mass = make_float2(0, 0);
	float2 separation_vector = make_float2(0, 0); 
	float2 perceived_velocity = make_float2(0, 0); 
	float2 alignment_vector = make_float2(0, 0); 
	float2 cohesion_vector = make_float2(0, 0); 

	for (int i = 0; i < size; i++){
		if (i != this_index){
			float dist = get_distance(boid_positions[this_index], 
				boid_positions[this_index + NB_OF_BOIDS], boid_positions[i], 
				boid_positions[i + NB_OF_BOIDS]);
			if (dist < VISION_DISTANCE){
				center_of_mass.x += boid_positions[i]; 
				center_of_mass.y += boid_positions[i + NB_OF_BOIDS]; 
				perceived_velocity.x += velocity[i];
				perceived_velocity.y += velocity[i + NB_OF_BOIDS];
			}
			if (dist < SEPARATION_DISTANCE){
				separation_vector.x -= ((- boid_positions[this_index] + boid_positions[i]) / SEPARATION_PARAMETER); 
				separation_vector.y -= ((- boid_positions[this_index + NB_OF_BOIDS] + boid_positions[i + NB_OF_BOIDS]) / SEPARATION_PARAMETER);
			} 
		}
	}
			 
	center_of_mass.x /= (size - 1);
	center_of_mass.y /= (size - 1);

	cohesion_vector.x = (center_of_mass.x - boid_positions[this_index]) / COHESION_PARAMETER;
	cohesion_vector.y = (center_of_mass.y - boid_positions[this_index + NB_OF_BOIDS]) / COHESION_PARAMETER;

	perceived_velocity.x /= (size - 1);
	perceived_velocity.y /= (size - 1);

	alignment_vector.x = (perceived_velocity.x - velocity[this_index]) / ALIGNMENT_PARAMETER;
	alignment_vector.y = (perceived_velocity.y - velocity[this_index + NB_OF_BOIDS]) / ALIGNMENT_PARAMETER;
	
	new_velocity[this_index] = velocity[this_index] + cohesion_vector.x + separation_vector.x + alignment_vector.x;
	new_velocity[NB_OF_BOIDS + this_index] = velocity[NB_OF_BOIDS + this_index] + cohesion_vector.y + separation_vector.y + alignment_vector.y;   
}

__global__
void computeVelocity(float* boid_positions, float* velocity, float *new_velocity, int size){
	int tid = threadIdx.x + blockIdx.x * gridDim.x; // handle the data at this index

	while (tid < NB_OF_BOIDS) {
		applyRules(boid_positions, velocity, new_velocity, tid, size); 
		tid += blockDim.x * gridDim.x;
	}
}

void cudaComputeVelocity(float* boid_positions, float* velocity, float *new_velocity, int size){
	computeVelocity << <NB_BLOCKS, NB_BLOCKS >> > (boid_positions, velocity, new_velocity, size);
}

__global__ 
void computeNewVelocity(float *old_velocity, float *cohesion, float *separation, float *alignment, float *new_velocity) {
	
	int tid = threadIdx.x + blockIdx.x * gridDim.x; // handle the data at this index

	while (tid < NB_OF_BOIDS) {
	
		new_velocity[tid] = old_velocity[tid] + cohesion[tid] + separation[tid] + alignment[tid];
		new_velocity[NB_OF_BOIDS + tid] = old_velocity[NB_OF_BOIDS + tid] + cohesion[NB_OF_BOIDS + tid] + separation[NB_OF_BOIDS + tid] + alignment[NB_OF_BOIDS + tid];
		tid += blockDim.x * gridDim.x;
	}
}

void cudaComputeNewVelocity(float *old_velocity, float *cohesion, float *separation, float *alignment, float *new_velocity) {
	computeNewVelocity << <64, 64 >> > (old_velocity, cohesion, separation, alignment, new_velocity);
}
