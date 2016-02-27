#pragma once
#include "Input.h"
#include "Texture.h"
#include "Ship.h"

class Level {
public:
    Level();
    //void add(Ship);
	void update(int delta);
    void draw(Graphics&);
    void notify(Input::Event e);
    void setForeground(Texture);
    void setBackground(Texture);
private:
    Ship player1;
    Ship player2;
    Texture foreground; // collidable
    Texture background; // pretty
	float gravity; // kg*px/s/s
};
