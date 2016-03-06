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
					   rotatingCounterclockwise(false),
					   hasGold(false) {
	setCollisionRadius(14);
    setMass(mass);
};

void Ship::update(int deltaT) {

	// apply booster force
	if(booster) {
		const float boosterForce = 900.0f; // kg*px/s/s
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

void Ship::onCollision(const RigidBody& other) {
	// near gold
	const Gold* g = dynamic_cast<const Gold*>(&other);
	// g will be null if colliding object is not gold
	if(g) {
		hasGold = true;
	}

	const Platform* p = dynamic_cast<const Platform*>(&other);
	if(p && hasGold) {
		hasGold = false;
	}

	float relativeXVel = getXVel() - other.getXVel();
	float relativeYVel = getYVel() - other.getYVel();

	// handle landing softly
	if( relativeYVel > -20 && // decending slowly
		relativeXVel < 10 &&   // relative to ground
		relativeXVel > -10 &&
		getRotation() < .4f &&  // vertically oriented
		getRotation() > -.4f &&
		getPosition().y > other.getPosition().y // must be above block
		) 
	{
		//neutralize downward force
		setYForce(std::max(0.f, getYForce())); 
		setYVel(std::max(0.f, getYVel()));
		setXVel(0);
		setRotation(0);
	}
	else reset();
}

void Ship::reset() {
	setXVel(0);
	setYVel(0);
	setPosition(spawn);
	setRotation(0);
	hasGold = false;
}
// private members
Point Ship::rotateAboutOrigin(Point p, float radians) {
	float newX = p.x * cos(radians) - p.y * sin(radians);
	float newY = p.x * sin(radians) + p.y * cos(radians);
	return Point(newX, newY);
}

void Ship::setSpawn(Point sp) {
    spawn = sp;
    setPosition(spawn);
}
