#pragma once
#include <glm/glm.hpp>

#include "loader.h"
#include "mesh.h"
#include "model.h"
#include "camera.h"

#include <GLFW/glfw3.h>
#include <vector>

class Demo {
public:
	GLFWwindow* window;
	GLuint shader_programme;
	GLint uniTrans;
	mesh* cube_mesh;
	model cube_model;
	int cube_count;
	std::vector<model_instance*> instances;
	std::vector<glm::vec3> rotations;
	std::vector<glm::vec3> translations;

	camera* cam;

	Demo(GLFWwindow* _window, camera* cam);
	~Demo();
	int load_assets();
	int run();
	void move_cubes();
};