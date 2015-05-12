#pragma once

#include "Input.h"
#include "Point.h"
#include "RigidBody.h"

class GameObject : public RigidBody {
public:
	GameObject();
	GameObject(Point p);
	virtual void draw() = 0;
	virtual void notify(Input::Event) { };
	virtual void update() { };
};
