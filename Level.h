#pragma once
#include <vector>
#include <memory>

#include "Input.h"
#include "Texture.h"
#include "GameObject.h"

class Level {
public:
    Level();
    void add(std::unique_ptr<GameObject>);
	void update(int delta);
    void draw(Graphics&);
    void notify(Input::Event e);
    void setForeground(Texture);
    void setBackground(Texture);
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Texture foreground; // collidable
    Texture background; // pretty
	float gravity; // kg*px/s/s
};
