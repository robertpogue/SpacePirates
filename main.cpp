#include "Graphics.h"
#include "Input.h"
#include "Level.h"
#include "Time.h"
#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_opengl.h"
#else
	#include "SDL/SDL.h"
	#include "SDL/SDL_opengl.h"
#endif
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char* args[]) {
    try {
	    Graphics::startUp();
        Level level;
	    level.loadLevel("aworks.bmp");
	    bool quit = false;
	    int lastFrame = getTime();
	    while(!quit) {
		    Input::Event e;
		    while((e = Input::nextInput()) != Input::NO_EVENT) {
			    if(e == Input::QUIT) quit = true;
			    level.notify(e);
		    }
		    // simulate game state

		    level.applyGravity();
		    level.detectCollisions();
		    level.update();
		    // draw screen
		    level.draw();
            Graphics::writeText("Hello World", 50, 50);
		    Graphics::flip();
		    int frameTime = getTime() - lastFrame;
		    float fps = 1000.f/frameTime;
		    lastFrame = getTime();
	    }
	    return 0;
    } catch(std::runtime_error e) {
        std::cout << "Error occurred: " << e.what();
        assert(0); //"Error occurred: " << e.what();
    }
    Graphics::shutDown();
    return 0;
}
