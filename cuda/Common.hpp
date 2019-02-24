#ifndef COMMON_HPP
#define COMMON_HPP

#include <GLFW/glfw3.h>

const float pi = 3.14f;

const int width = 1600;
const int height = 900;

// Hyperparameters  - lower = stronger

const float cohesion_parameter = 50.0f;
const float separation_parameter = 5.0f;
const float alignment_parameter = 50.0f;

const float separation_distance = 0.05f;

const float vision_distance = 2.0f;

const float v_lim = .03;



typedef struct Color {

	GLfloat r, g, b;

} Color;

const Color colors[8] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, {1, 1, 1} };

#endif