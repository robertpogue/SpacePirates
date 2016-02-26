#pragma once

#include "Color.h"
#include "GameObject.h"
#include "Input.h"
#include "Level.h"
#include "Point.h"
//#include "Texture.h"

enum class Player {One, Two };

class Ship :public GameObject {
public:
	float mass; // kg
	long lastUpdate;
	Player player;
	Ship(Player, float mass = 10.0f);
	void notify(Input::Event);
    //void setTexture(Texture& t);
	// inherited from RigidBody
	void onCollision(const RigidBody& other);
	void setSpawn(Point);
	void setColor(Color);
	void update();
private:
	//Texture texture;
	Point spawn;
	bool rotatingClockwise;
	bool rotatingCounterclockwise;
	bool booster;
	bool hasGold;
	Point rotateAboutOrigin(Point p, float radians);
	void reset();
};
