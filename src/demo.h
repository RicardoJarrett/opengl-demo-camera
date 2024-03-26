#pragma once
#include <glm/glm.hpp>

#include "loader.h"
#include "mesh.h"
#include "model.h"

#include <GLFW/glfw3.h>
#include <vector>

class Demo {
public:
	GLFWwindow* window;
	GLint uniTrans;
	mesh* cube_mesh;
	model cube_model;
	int cube_count;
	std::vector<model_instance*> instances;
	std::vector<glm::vec3> rotations;
	std::vector<glm::vec3> translations;

	Demo(GLFWwindow* _window);
	~Demo();
	int load_assets();
	int run();
	void move_cubes();
};