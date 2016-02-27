#pragma once
#include "Input.h"
#include "Ship.h"

class Level {
public:
    Level();
    //void add(Ship);
	void update(int delta);
    void draw(Graphics&);
    void notify(Input::Event e);
private:
    Ship player1;
    Ship player2;
	float gravity; // kg*px/s/s
};
