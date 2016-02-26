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
private:
    Ship player1;
    Ship player2;
	float gravity; // kg*px/s/s
};
