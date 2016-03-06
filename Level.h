#pragma once
#include <vector>
#include <memory>

#include "Input.h"
#include "Image.h"
#include "Ship.h"

class Level {
public:
    Level();
    void add(Ship);
	void update(int delta);
    void draw(Graphics&);
    void notify(Input::Event e);
    void setLevel(Image);
    void setBackground(Image);
private:
    std::vector<Ship> ships;
    Image level; // collidable
    Image background; // pretty
	float gravity; // kg*px/s/s

    void detectCollisions();
};
