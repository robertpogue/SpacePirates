#pragma once
#include <vector>
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
    void    setImage(Image); // calculates center of mass and builds collision model
    Point   getCenterOfMass() const;
    std::vector<Point> collisionPoints; // relative to center of mass
private:
	Image image;
    Point centerOfMass; // on image in px; origin bottom left; +x right; +y up
	Point spawn;
	bool rotatingClockwise;
	bool rotatingCounterclockwise;
	bool booster;
};
