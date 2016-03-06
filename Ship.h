#pragma once
#include "Color.h"
#include "GameObject.h"
#include "Input.h"
#include "Point.h"
#include "Image.h"
#include "GameObject.h"

enum class Player {One, Two };

class Ship : public GameObject {
public:
	float mass; // kg
	long lastUpdate;
	Player player;
	Ship(Player = Player::One, float mass = 10.0f);
	void notify(Input::Event);
    //void setTexture(Texture& t);
	// inherited from RigidBody
	void    setSpawn(Point);
    void    respawn();
	//void  setColor(Color);
	void    update(int delta); // time elapsed in ms
    Image   getImage() const;
    void    setImage(Image);
private:
	Image image;
	Point spawn;
	bool rotatingClockwise;
	bool rotatingCounterclockwise;
	bool booster;
	Point rotateAboutOrigin(Point p, float radians);
};
