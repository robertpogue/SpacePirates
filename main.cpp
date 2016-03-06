#include <exception>
#include <string>
#include <assert.h>
#include <memory>
#include "SDL.h"
#include "Graphics.h"
#include "Input.h"
#include "Level.h"
#include "Ship.h"
#include "Time.h"
using namespace std;

int main(int argc, char ** argv) {
    try {
        // game engine subsystems
        Graphics graphics;
        Level level;
        Time time;

        // load level
        level.setLevel(graphics.load("levels/mountains.bmp"));
        level.setBackground(graphics.load("levels/summer_sky.bmp"));
        auto player1 = Ship();
        auto player2 = Ship(Player::Two);
        player1.setPosition(Point(50, 250));
        player2.setPosition(Point(100, 250));
        player1.setImage(graphics.load("ships/ship1.bmp"));
        player2.setImage(graphics.load("ships/ship2.bmp"));
        level.add(player1);
        level.add(player2);

        // rendering loop
        bool quit{ false };
        while(!quit) {
            // calculate framerate
            int frameTime = time.frame();
            int fps = (int)round(1000.f / frameTime);
            Input::Event e;
            do { // handle input
                e = Input::nextInput();
                if(e == Input::QUIT) quit = true;
                level.notify(e);
            } while(e != Input::NO_EVENT);
            graphics.clear();
            level.update(frameTime);
            level.draw(graphics);
            graphics.draw(std::to_string(fps) + " fps", Point(25, graphics.getHeight() - 10.f));
            graphics.present();
        }

    } catch(std::exception e) {
        return EXIT_FAILURE; // error return code
    }
    return EXIT_SUCCESS; // normal program exit
}