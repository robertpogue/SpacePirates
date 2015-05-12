#include "Ship.h"
#include "Color.h"
#include "Gold.h"
#include "Graphics.h"
#include "Input.h"
#include "Platform.h"
#include "Point.h"
#include "Time.h"
#include <cmath>

Ship::Ship(Player p, float mass) : booster(false), player(p),
                       rotatingClockwise(false),
					   rotatingCounterclockwise(false),
					   hasGold(false), 
					   color(1, 1, 1) {
	//lastUpdate = getTime();
	setCollisionRadius(14);
    setMass(mass);
};

void Ship::update() {
	// time elapsed since last update
	long deltaT = getTime() - lastUpdate; // ms
	lastUpdate = getTime();

	// apply booster force
	if(booster) {
		const float boosterForce = 900.0f; // kg*px/s/s
		applyForce(-sin(getRot()) * boosterForce, cos(getRot()) * boosterForce);
	}
	float turnRate = 5;// radians/second
	if(rotatingClockwise) setRot(getRot() + turnRate * deltaT/1000);
	if(rotatingCounterclockwise) setRot(getRot() - turnRate * deltaT/1000);

	// allow rigidbody to simulate physics
	RigidBody::update();
}

void Ship::draw() {
	Point shipTop(0,12);
	shipTop = rotateAboutOrigin(shipTop, getRot());
	Point shipBottomRight(6,-8);
	shipBottomRight = rotateAboutOrigin(shipBottomRight, getRot());
	Point shipBottomLeft(-6,-8);
	shipBottomLeft = rotateAboutOrigin(shipBottomLeft, getRot());
	Graphics::triangle(shipTop + getPos(),
		               shipBottomLeft + getPos(),
					   shipBottomRight + getPos(),
					   color);
	if(booster) {
		Point flameBottomRight(-4,-6);
		Point flameBottomLeft(4,-6);
		Point flameTop(0,-20);
		flameBottomRight = rotateAboutOrigin(flameBottomRight, getRot());
		flameBottomLeft = rotateAboutOrigin(flameBottomLeft, getRot());
		flameTop = rotateAboutOrigin(flameTop, getRot());
		Graphics::triangle(flameBottomLeft + getPos(), 
			               flameBottomRight + getPos(),
						   flameTop + getPos(),
						   Color(200,200,40));
	}
	if(hasGold) {
		Point goldBottomRight(2,-4);
		Point goldBottomLeft(-2,-4);
		Point goldTop(0,5);
		goldBottomRight = rotateAboutOrigin(goldBottomRight, getRot());
		goldBottomLeft = rotateAboutOrigin(goldBottomLeft, getRot());
		goldTop = rotateAboutOrigin(goldTop, getRot());
		Graphics::triangle(goldBottomLeft + getPos(), 
			               goldBottomRight + getPos(),
						   goldTop + getPos(),
						   Color(255,255,255));
	}
}

void Ship::notify(Input::Event e) {
	if(player == PLAYER_ONE) {
		if(e == Input::ARROW_UP) booster = true;
		if(e == Input::ARROW_UP_RELEASE) booster = false;
		if(e == Input::ARROW_LEFT) rotatingClockwise = true;
		if(e == Input::ARROW_LEFT_RELEASE) rotatingClockwise = false;
		if(e == Input::ARROW_RIGHT) rotatingCounterclockwise = true;
		if(e == Input::ARROW_RIGHT_RELEASE) rotatingCounterclockwise = false;
	}
	if (player == PLAYER_TWO) {
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
		getRot() < .4f &&  // vertically oriented
		getRot() > -.4f &&
		getPos().y > other.getPos().y // must be above block
		) 
	{
		//neutralize downward force
		setYForce(std::max(0.f, getYForce())); 
		setYVel(std::max(0.f, getYVel()));
		setXVel(0);
		setRot(0);
	}
	else reset();
}

void Ship::reset() {
	setXVel(0);
	setYVel(0);
	setPos(spawn);
	setRot(0);
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
	setPos(spawn);
}

void Ship::setColor(Color c) {
	color = c;
}
