#pragma once
#include "utility.h"
#include <GLFW/glfw3.h>

struct camera {
	glm::mat4 rotation, translation;
	float view_angle, width, height, depth;

	camera();
	camera(glm::mat4 _rotation, glm::mat4 _translation, float _view_angle, float _width, float _height, float _depth);

	glm::mat4 get_transform();

	void rotate(glm::vec3 rot);
	void translate(glm::vec3 trans);
	void move_forward(float speed);
	void strafe(float speed);
};