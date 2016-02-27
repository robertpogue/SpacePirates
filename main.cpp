#include <SDL.h>
#include <exception>
#include <string>
#include <assert.h>
#include <memory>

#include "Graphics.h"
#include "Input.h"
#include "Level.h"
#include "Ship.h"
#include "Time.h"
using namespace std;

int main(int argc, char ** argv) {
    // variables on the stack
    Input::Event e;
    bool quit{ false };
    
    // game engine subsystems
    Graphics graphics;
    Level level;
    Time time;

    // load level
    level.setForeground(graphics.load("levels/mountains.bmp"));
    level.setBackground(graphics.load("levels/summer_sky.bmp"));
    auto player1 = make_unique<Ship>();
    auto player2 = make_unique<Ship>(Player::Two);
    player1->setPos(Point(50, 250));
    player2->setPos(Point(100, 250));
    player1->setTexture(graphics.load("ships/ship1.bmp"));
    player2->setTexture(graphics.load("ships/ship2.bmp"));
    level.add(move(player1));
    level.add(move(player2));

    // rendering loop
    while(!quit) {
        // calculate framerate
        int frameTime = time.frame();
        int fps = round(1000.f / frameTime);

        do { // handle input
            e = Input::nextInput();
            if(e == Input::QUIT) quit = true;
            level.notify(e);
        } while(e != Input::NO_EVENT);
        graphics.clear();
        level.update(frameTime);
        level.draw(graphics);
        graphics.writeText(std::to_string(fps) + " fps", Point(5, graphics.getHeight() - 2.f));
        graphics.present();
    }
    return 0;
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
