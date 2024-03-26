#include "camera.h"
#include <iostream>

camera::camera() {
	rotation = glm::mat4(1.0f);
	translation = glm::mat4(1.0f);
	view_angle = glm::radians(45.0f);
	width = 480.0f;
	height = 360.f;
	depth = 1000.0f;
}

camera::camera(glm::mat4 _rotation, glm::mat4 _translation, float _view_angle, float _width, float _height, float _depth) {
	rotation = _rotation;
	translation = _translation;
	view_angle = _view_angle;
	width = _width;
	height = _height;
	depth = _depth;
}

glm::mat4 camera::get_transform() {
	glm::mat4 trans = rotation * translation * glm::mat4(1.0f);
	return trans;
}