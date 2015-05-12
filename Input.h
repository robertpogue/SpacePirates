#pragma once

namespace Input {
	enum Event {
		NO_EVENT,
		QUIT,
		ARROW_UP, ARROW_UP_RELEASE,
		ARROW_DOWN, ARROW_DOWN_RELEASE,
		ARROW_LEFT, ARROW_LEFT_RELEASE,
		ARROW_RIGHT, ARROW_RIGHT_RELEASE,
		KEY_A, KEY_A_RELEASE,
		KEY_S, KEY_S_RELEASE,
		KEY_D, KEY_D_RELEASE,
		KEY_W, KEY_W_RELEASE
	};
	// returns NO_EVENT when all inputs are handled
	// expects sdl to be initialized
	Event nextInput();
}
