#include "camera.h"
#include <iostream>

camera::camera() {
	rotation = glm::mat4(1.0f);
	v3Rot = glm::vec3(1.0, 1.0, 1.0);
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

void camera::rotate(glm::vec3 rot) {
	glm::mat4 new_rot = glm::mat4(1.0f);
	new_rot = glm::rotate(new_rot, rot.x, glm::vec3(1.0, 0.0, 0.0));
	new_rot = glm::rotate(new_rot, rot.y, glm::vec3(0.0, 1.0, 0.0));
	new_rot = glm::rotate(new_rot, rot.z, glm::vec3(0.0, 0.0, 1.0));
	rotation = new_rot;
}
void camera::translate(glm::vec3 trans) {
	glm::mat4 new_trans = glm::mat4(1.0f);
	new_trans = glm::translate(new_trans, trans);
	translation = new_trans;
}

void camera::move_forward(float speed) {
	//std::cout << speed << "\n";
	glm::mat4 inverted = glm::inverse(get_transform());
	glm::vec3 forward = normalize(glm::vec3(inverted[2]));
	forward *= speed;
	translation = glm::translate(translation, forward);
}

void camera::strafe(float speed) {
	glm::mat4 inverted = glm::inverse(get_transform());
	glm::vec3 strafe = normalize(glm::vec3(inverted[0]));
	strafe *= speed;
	translation = glm::translate(translation, strafe);
}