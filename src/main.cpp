#include "main.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "demo.h"

using namespace std;

float x_pos = 0.0f;
float y_pos = 0.0f;
float z_pos = 0.0f;

float speed = 0.1f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_RIGHT && ((action == GLFW_PRESS) || (action == GLFW_REPEAT))) {
		x_pos += speed;
	}
	else if (key == GLFW_KEY_LEFT && ((action == GLFW_PRESS) || (action == GLFW_REPEAT))) {
		x_pos -= speed;
	}
	else if (key == GLFW_KEY_UP && ((action == GLFW_PRESS) || (action == GLFW_REPEAT))) {
		z_pos += speed;
	}
	else if (key == GLFW_KEY_DOWN && ((action == GLFW_PRESS) || (action == GLFW_REPEAT))) {
		z_pos -= speed;
	}
}

int create_window(GLFWwindow** win) {
	*win = glfwCreateWindow(640, 480, "Test", NULL, NULL);	//windowed
	//GLFWwindow* window = glfwCreateWindow(640, 480, "Test", glfwGetPrimaryMonitor(), NULL);	//fullscreen
	if (!*win) {
		printf("ERROR: Unable to create Window.");
		return 0;
	}
	else {
		glfwMakeContextCurrent(*win);
		glfwSetKeyCallback(*win, key_callback);

		glewExperimental = GL_TRUE;
		glewInit();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	return 1;
}

int init(GLFWwindow** window) {
	if (!glfwInit()) {
		printf("Unable to initialse GLFW.");
		return 0;
	}
	else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}
	if (!create_window(window)) {
		cout << "Error creating window.\n";
		return -1;
	}

	return 1;
}

int main() {
	
	GLFWwindow* window;
	if (init(&window) < 0) {
		cout << "Error initialising.\n";
		return -1;
	}
	
	Demo demo(window);
	int load_return = demo.load_assets();
	if (load_return < 0) {
		std::cout << "Load: " << load_return << "\n";
	}
	int demo_return = demo.run();

	glfwDestroyWindow(window);
	glfwTerminate();
	return demo_return;
}