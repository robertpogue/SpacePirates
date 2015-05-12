#pragma once

#include "GameObject.h"
#include "Input.h"
#include <memory>
#include <string>
#include <vector>

class Level {
public:
	void loadLevel(std::string path);
	void draw();
	void update();
	void notify(Input::Event e);
	void applyGravity();
	void detectCollisions();
private:
	float gravityAcceleration;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	bool areColliding(const GameObject* const c1, const GameObject* const c2); // bad place
};
