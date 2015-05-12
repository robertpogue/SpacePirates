#include "Time.h"
#ifdef _WIN32
	#include "SDL.h"
#else
	#include "SDL/SDL.h"
#endif

int getTime() {
	return (int)(SDL_GetTicks());
}
