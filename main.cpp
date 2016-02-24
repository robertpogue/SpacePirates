#include <SDL.h>
#include <exception>
#include <string>
#include <assert.h>

int main(int argc, char ** argv) {
    try {
        int result = SDL_Init(SDL_INIT_VIDEO);
        assert(result);

        SDL_Window* window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        assert(window);

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        assert(renderer);

        std::string imagePath = "hello.bmp";
        SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
        assert(bmp);

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);
        assert(texture);

        // rendering loop
        for(int i = 0; i < 3; ++i) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
        }

        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    } catch(std::exception) {
        return 1;
    }
}
/*#include "Graphics.h"
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

// screen dimensions
const int SCREEN_WIDTH = 640; // px
const int SCREEN_HEIGHT = 480; // px

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
*/