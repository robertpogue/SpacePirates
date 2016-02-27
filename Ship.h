#pragma once

#include "Color.h"
#include "GameObject.h"
#include "Input.h"
#include "Point.h"
#include "Texture.h"
#include "Graphics.h"

enum class Player {One, Two };

class Ship :public GameObject {
public:
	float mass; // kg
	long lastUpdate;
	Player player;
	Ship(Player = Player::One, float mass = 10.0f);
	void notify(Input::Event);
    //void setTexture(Texture& t);
	// inherited from RigidBody
	void onCollision(const RigidBody& other);
	void setSpawn(Point);
	//void setColor(Color);
	void update(int delta); // time elapsed in ms
    Texture getTexture() const;
    void    setTexture(Texture);
    void    draw(Graphics&);
private:
	Texture texture;
	Point spawn;
	bool rotatingClockwise;
	bool rotatingCounterclockwise;
	bool booster;
	bool hasGold;
	Point rotateAboutOrigin(Point p, float radians);
	void reset();
};
