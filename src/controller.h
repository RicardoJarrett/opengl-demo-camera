#pragma once

struct controller {
	int forward, strafe, turn_x, turn_y;
	void reset();
};