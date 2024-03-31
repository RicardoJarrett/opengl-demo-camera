#pragma once

struct controller {
	float forward, strafe, turn_x, turn_y;
	void reset();
	bool buttons[14];
	float axes[6];
	enum button {
		a, b, x, y,
		lb, rb,
		back, start,
		l3, r3,
		up, right, down, left
	};
	enum axis {
		l_x, l_y,
		r_x, r_y,
		lt, rt
	};
	void process_input();
};