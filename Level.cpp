#include "Level.h"
#include "Color.h"
#include "Block.h"
#include "Gold.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Texture.h"
#include "Platform.h"
#include "Point.h"
#include "Ship.h"

void Level::loadLevel(std::string path) {
	/*Color blockColor(0,0,0);
	Color player1Color(150,150,255);
	Color player2Color(255,0,0);
	Color goldColor(255,255,0);
	Color platformColor(0,255,0);
	Color groundColor(204,102,51 );
	gravityAcceleration = -20.0f; // kg*px/s/s

	Texture image;
	image.load(path.c_str());
	Color color = image.getPixel(0,0);
	for(int w = 0; w < image.width(); w++) {
		for(int h=0; h < image.height(); h++) {
            float xPx = Block::size/2.0f + (w*Block::size);
			float yPx = (image.height()*Block::size) - (Block::size/2.0f + (h*Block::size));
			Color px = image.getPixel(w,h);
			if( px == blockColor) {
				std::shared_ptr<Block> block(new Block(Point(xPx, yPx)));
				block->color = blockColor;
				gameObjects.push_back(block);
			} else if(px == player1Color) {
				std::shared_ptr<Ship> p1(new Ship(PLAYER_ONE));
				p1->setColor(player1Color);
				p1->setDynamic(true);
				p1->setSpawn(Point(xPx, yPx));
				gameObjects.push_back(p1);
			} else if(px == player2Color) {
				std::shared_ptr<Ship> p2(new Ship(PLAYER_TWO));
				p2->setColor(player2Color);
				p2->setSpawn(Point(xPx, yPx));
				p2->setDynamic(true);
				gameObjects.push_back(p2);
			} else if(px == goldColor) {
				std::shared_ptr<Gold> gold(new Gold(Point(xPx, yPx)));
				gameObjects.push_back(gold);
			} else if(px == platformColor) {
				std::shared_ptr<Platform> platform(new Platform(Point(xPx, yPx)));
				gameObjects.push_back(platform);
			} else if(px == groundColor) {
        //TODO: this probably calls for a new Ground class
				std::shared_ptr<Block> block(new Block(Point(xPx, yPx)));
				block->color = groundColor;
				gameObjects.push_back(block);
			}
		}
	}*/
}

void Level::draw() {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->draw();
	}
}

void Level::notify(Input::Event e) {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->notify(e);
	}
}

void Level::update() {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->update();
	}
}

void Level::applyGravity() {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		float gravityForce = gravityAcceleration * gameObjects.at(i)->getMass();
		gameObjects.at(i)->applyForce(0.f, gravityForce);
	}
}

void Level::detectCollisions() {
	for(unsigned int i = 0; i < gameObjects.size(); i++) {
		if(!gameObjects[i]->isDynamic()) continue;
		for(unsigned int j = 0; j < gameObjects.size(); j++) {
			if(i==j) continue; // don't test for self-colision
			if(areColliding(gameObjects[i].get(), gameObjects[j].get())) {
				gameObjects[i]->onCollision(*gameObjects[j]);
				gameObjects[j]->onCollision(*gameObjects[i]);
			}
		}
	}
}

bool Level::areColliding(const GameObject* const c1, const GameObject* const c2) {
	Point difference = c1->getPos()-c2->getPos();
	int radiusSquared = c1->getCollisionRadius() * c1->getCollisionRadius() + 
		                c2->getCollisionRadius() * c2->getCollisionRadius();
	if(difference.squareMagnitude() < radiusSquared) 
		return true;
	else return false;
}
