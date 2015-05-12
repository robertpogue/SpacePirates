#include "Input.h"
#ifdef _WIN32
	#include "SDL.h"
#else
	#include "SDL/SDL.h"
#endif
#include <memory>

using namespace Input;

Event Input::nextInput() {
	static SDL_Event sdlEvent;

	// get next sdl event
	while(SDL_PollEvent(&sdlEvent)) {
		if(sdlEvent.type == SDL_QUIT) return QUIT;
		if(sdlEvent.type == SDL_KEYDOWN) {
			if(sdlEvent.key.keysym.sym == SDLK_UP) return ARROW_UP;
			if(sdlEvent.key.keysym.sym == SDLK_DOWN) return ARROW_DOWN;
			if(sdlEvent.key.keysym.sym == SDLK_LEFT) return ARROW_LEFT;
			if(sdlEvent.key.keysym.sym == SDLK_RIGHT) return ARROW_RIGHT;
			if(sdlEvent.key.keysym.sym == SDLK_w) return KEY_W;
			if(sdlEvent.key.keysym.sym == SDLK_a) return KEY_A;
			if(sdlEvent.key.keysym.sym == SDLK_d) return KEY_D;
			if(sdlEvent.key.keysym.sym == SDLK_s) return KEY_S;
		}
		if(sdlEvent.type == SDL_KEYUP) {
			if(sdlEvent.key.keysym.sym == SDLK_UP) return ARROW_UP_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_DOWN) return ARROW_DOWN_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_LEFT) return ARROW_LEFT_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_RIGHT) return ARROW_RIGHT_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_w) return KEY_W_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_a) return KEY_A_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_d) return KEY_D_RELEASE;
			if(sdlEvent.key.keysym.sym == SDLK_s) return KEY_S_RELEASE;
		}
	}
	return NO_EVENT;
}
