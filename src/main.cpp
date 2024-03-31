#include "main.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.h"
#include "demo.h"
#include "controller.h"

using namespace std;

Demo* demo;

camera cam;

glm::vec3 pos, rot;

float speed = 0.1f;

controller control;

void update_camera() {
	control.process_input();
	rot += glm::vec3(control.turn_x * speed, control.turn_y * speed, 0.0);
	cam.rotate(rot);
	cam.move_forward(speed * control.forward);
	cam.strafe(speed * control.strafe);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	control.reset();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	bool pressed = false;
	bool ctrl = false;
	bool shift = false;

	if ((action == GLFW_PRESS) || (action == GLFW_REPEAT)) {
		pressed = true;
	}
	if (mods == GLFW_MOD_CONTROL) {
		ctrl = true;
	}
	if (mods == GLFW_MOD_SHIFT) {
		shift = true;
	}
	if (key == GLFW_KEY_RIGHT && pressed) {
		if (ctrl) {
			control.turn_y = 1;
		}
		else {
			control.strafe = -1;
		}
	}
	else if (key == GLFW_KEY_LEFT && pressed) {
		if (ctrl) {
			control.turn_y = -1;
		}
		else {
			control.strafe = 1;
		}
	}
	else if (key == GLFW_KEY_UP && pressed) {
		if (ctrl) {
			control.turn_x = -1;
		}
		else {
			control.forward = 1;
		}
	}
	else if (key == GLFW_KEY_DOWN && pressed) {
		if (ctrl) {
			control.turn_x = 1;
		}
		else {
			control.forward = -1;
		}
	}
	
	demo->update_camera(rot, speed);
}

int create_window(GLFWwindow** win) {
	*win = glfwCreateWindow(640, 480, "Test", NULL, NULL);	//windowed
	//*win = glfwCreateWindow(640, 480, "Test", glfwGetPrimaryMonitor(), NULL);	//fullscreen
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
	
	demo = new Demo(window, &cam, &control);
	int load_return = demo->load_assets();
	if (load_return < 0) {
		std::cout << "Load: " << load_return << "\n";
	}
	int demo_return = demo->run();

	glfwDestroyWindow(window);
	glfwTerminate();
	return demo_return;
}