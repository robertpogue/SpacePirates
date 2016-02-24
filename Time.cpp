#include "Time.h"
#include "SDL.h"

int getTime() {
	return (int)(SDL_GetTicks());
}
