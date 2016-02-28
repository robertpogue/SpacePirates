#pragma once
#include <vector>
#include <memory>

#include "Input.h"
#include "Image.h"
#include "GameObject.h"

class Level {
public:
    Level();
    void add(std::unique_ptr<GameObject>);
	void update(int delta);
    void draw(Graphics&);
    void notify(Input::Event e);
    void setLevel(Image);
    void setBackground(Image);
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Image level; // collidable
    Image background; // pretty
	float gravity; // kg*px/s/s

    void detectCollisions();
};
