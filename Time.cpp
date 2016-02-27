#include "Time.h"
#include "SDL.h"

// utility function
int getTime() {
    return (int)(SDL_GetTicks());
}

Time::Time() : lastFrame(0) {}



int Time::frame() {
    int now = getTime();
    int frameTime = now - lastFrame;
    lastFrame = now;
    return frameTime;
}
