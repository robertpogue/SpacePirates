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

// declare utility functions
bool areColliding(const GameObject& c1, const GameObject& c2);

Level::Level() : gravity(-10) {
    
}
void Level::add(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Level::update(int delta) {
    for(auto& object : gameObjects) {
        // apply gravity
        float gravityForce = gravity * object->getMass();
        object->applyForce(0.f, gravityForce);

        // allow object to update
        object->update(delta);
    }
    

    //a
    /*if(areColliding(player1, player2)) {
        player1.setPos(Point(50, 150));
        player1.setXVel(0);
        player1.setYVel(0);
        player2.setPos(Point(100, 150));
        player2.setXVel(0);
        player2.setYVel(0);
    }*/
}

void Level::draw(Graphics& graphics) {
    Point screenCenter{ graphics.screenWidth / 2, graphics.screenHeight / 2 };
    graphics.blit(background, screenCenter, 0);
    graphics.blit(level, screenCenter, 0);
    for(auto& object : gameObjects) {
        object->draw(graphics);
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
    for(auto& object : gameObjects) {
        object->notify(e);
    }
}

void Level::detectCollisions() {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		if(!gameObjects[i]->isDynamic()) continue;
		for(unsigned int j = i+1; j < gameObjects.size(); j++) {
			if(i==j) continue; // don't test for self-colision
			if(areColliding(gameObjects[i].get(), gameObjects[j].get())) {
				gameObjects[i]->onCollision(*gameObjects[j]);
				gameObjects[j]->onCollision(*gameObjects[i]);
			}
		}
	}
}


