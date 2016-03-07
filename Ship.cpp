#include "Ship.h"
#include "Color.h"
#include "Gold.h"
#include "Graphics.h"
#include "Input.h"
#include "Platform.h"
#include "Point.h"
#include <cmath>
#include <algorithm>

Ship::Ship(Player p, float mass) : booster(false), player(p),
                       rotatingClockwise(false),
					   rotatingCounterclockwise(false) {
	setCollisionRadius(14);
    setMass(mass);
};

void Ship::update(int deltaT) {

	// apply booster force
	if(booster) {
		const float boosterForce = 500.0f; // kg*px/s/s
		applyForce(-sin(getRotation()) * boosterForce, cos(getRotation()) * boosterForce);
	}
	float turnRate = 5;// radians/second
	if(rotatingClockwise) setRotation(getRotation() + turnRate * deltaT/1000);
	if(rotatingCounterclockwise) 
        setRotation(getRotation() - turnRate * deltaT/1000);

	// allow rigidbody to simulate physics
	RigidBody::update(deltaT);
}

Image Ship::getImage() const {
    return image;
}

void Ship::setImage(Image i) {
    image = i;
    // calculate center of mass
    centerOfMass.x = image.getWidth() / 2.f;
    centerOfMass.y = image.getHeight() / 2.f;
}

void Ship::notify(Input::Event e) {
	if(player == Player::One) {
		if(e == Input::ARROW_UP) booster = true;
		if(e == Input::ARROW_UP_RELEASE) booster = false;
		if(e == Input::ARROW_LEFT) rotatingClockwise = true;
		if(e == Input::ARROW_LEFT_RELEASE) rotatingClockwise = false;
		if(e == Input::ARROW_RIGHT) rotatingCounterclockwise = true;
		if(e == Input::ARROW_RIGHT_RELEASE) rotatingCounterclockwise = false;
	}
	if (player == Player::Two) {
		if(e == Input::KEY_W) booster = true;
		if(e == Input::KEY_W_RELEASE) booster = false;
		if(e == Input::KEY_A) rotatingClockwise = true;
		if(e == Input::KEY_A_RELEASE) rotatingClockwise = false;
		if(e == Input::KEY_D) rotatingCounterclockwise = true;
		if(e == Input::KEY_D_RELEASE) rotatingCounterclockwise = false;
	}
}

void Ship::setSpawn(Point sp) {
    spawn = sp;
    setPosition(spawn);
}

void Ship::respawn() {
	setXVel(0);
	setYVel(0);
	setPosition(spawn);
	setRotation(0);
}

Point Ship::getCenterOfMass() const {
    return centerOfMass;
}

// private members
Point Ship::rotateAboutOrigin(Point p, float radians) {
	float newX = p.x * cos(radians) - p.y * sin(radians);
	float newY = p.x * sin(radians) + p.y * cos(radians);
	return Point(newX, newY);
}


