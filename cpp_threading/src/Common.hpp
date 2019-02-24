#ifndef COMMON_HPP
#define COMMON_HPP

#include <GLFW/glfw3.h>

const float pi = 3.14f;

const int width = 800;
const int height = 600;

// Hyperparameters  - lower = stronger

const float cohesion_parameter = 2000.0f;
const float separation_parameter = 10.0f;
const float alignment_parameter = 500.0f;

const float separation_distance = 0.03f;

const float v_lim = .01;



typedef struct Color {

	GLfloat r, g, b;

} Color;

const Color colors[8] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, {1, 1, 1} };

#endif