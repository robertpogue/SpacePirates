#pragma once
#include "Input.h"
#include "Ship.h"

class Level {
public:
    Level();
    //void add(Ship);
	void update();
    void draw(Graphics&);
    void notify(Input::Event e);
	/*void applyGravity();
	void detectCollisions();*/
//private:
    //Ship player1;
    /*
	float gravityAcceleration;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	bool areColliding(const GameObject* const c1, const GameObject* const c2); // bad place
    */
};
