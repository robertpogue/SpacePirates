#pragma once

#include "Color.h"
#include "GameObject.h"
#include "Input.h"
#include "Level.h"
#include "Point.h"

enum Player {PLAYER_ONE, PLAYER_TWO };

struct Ship :public GameObject {
	float mass; // kg
	long lastUpdate;
	Player player;
	Ship(Player, float mass = 10.0f);
	void notify(Input::Event);
	void draw();
	// inherited from RigidBody
	void onCollision(const RigidBody& other);
	void setSpawn(Point);
	void setColor(Color);
	void update();
private:
	Color color;
	Point spawn;
	bool rotatingClockwise;
	bool rotatingCounterclockwise;
	bool booster;
	bool hasGold;
	Point rotateAboutOrigin(Point p, float radians);
	void reset();
};
