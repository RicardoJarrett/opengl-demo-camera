#include "controller.h"

#include <GLFW/glfw3.h>
#include <iostream>

void controller::reset() {
	forward = 0;
	strafe = 0;
	turn_x = 0;
	turn_y = 0;
}

float trim_axis(float axis) {
	const float trim = 0.2;
	if ((axis < trim) && (axis > (-1.0 * trim))) {
		return 0.0f;
	}
	else if (axis > trim) {
		float tmp = axis;
		tmp -= trim;
		tmp /= (1.0 - trim);
		return tmp;
	}
	else if (axis < (-1 * trim)) {
		float tmp = axis;
		tmp += trim;
		tmp /= (1.0 - trim);
		return tmp;
	}
}

void controller::process_input() {
	int b_count, a_count;
	const unsigned char* _buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &b_count);
	const float* _axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &a_count);
	for (int btn = 0; btn < b_count; btn++) {
		if (_buttons[btn] == GLFW_PRESS) {
			buttons[btn] = true;
		}
		else {
			buttons[btn] = false;
		}
	}

	for (int axis = 0; axis < a_count; axis++) {
		axes[axis] = _axes[axis];
	}

	forward = trim_axis(axes[axis::l_y]) * -1.0;

	strafe = trim_axis(axes[axis::l_x]) * -1.0;

	turn_x = trim_axis(axes[axis::r_y]);
	turn_y = trim_axis(axes[axis::r_x]);
}