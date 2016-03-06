#include "Level.h"
#include "Color.h"
#include "Block.h"
#include "Gold.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Image.h"
#include "Platform.h"
#include "Point.h"
#include "Ship.h"

Level::Level() : gravity(-10) {
    
}
void Level::add(Ship ship) {
    ships.push_back(ship);
}

void Level::update(int delta) {
    for(auto& ship : ships) {
        // apply gravity
        float gravityForce = gravity * ship.getMass();
        ship.applyForce(0.f, gravityForce);

        // allow object to update
        ship.update(delta);

        // collision detection
        /*Color c = level.getPixel(object->getPosition());
        Color none = Color(255, 0, 255);
        if(!(c == none)) {
            object->setPosition(Point(50, 150));
            object->setXVel(0);
            object->setYVel(0);
            object->setRotation(0);
        }*/
    }
    
    

    /*if(areColliding(player1, player2)) {

        player2.setPos(Point(100, 150));
        player2.setXVel(0);
        player2.setYVel(0);
        player2.setRot(0);
    }*/
}

void Level::draw(Graphics& graphics) {
    Point screenCenter{ graphics.screenWidth / 2, graphics.screenHeight / 2 };
    graphics.blit(background, screenCenter, 0);
    graphics.blit(level, screenCenter, 0);
    for(auto ship : ships) {
        graphics.draw(ship);
    }  
}

void Level::setLevel(Image i) {
    level = i;
}

void Level::setBackground(Image t) {
    background = t;
}

void Level::notify(Input::Event e) {
	//for(unsigned int i = 0; i < gameObjects.size(); i++) {
		//gameObjects.at(i)->notify(e);
	//}
    for(auto& ship : ships) {
        ship.notify(e);
    }
}

void Level::detectCollisions() {
	for(unsigned int i = 0; i < ships.size(); i++) {
		if(!ships[i].isDynamic()) continue;
		for(unsigned int j = i+1; j < ships.size(); j++) {
			if(i==j) continue; // don't test for self-colision
			// test collisions
		}
	}
}


