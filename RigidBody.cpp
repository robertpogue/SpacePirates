#include "RigidBody.h"
#include "Point.h"
#include "Time.h"
#include <math.h>

const static float PI = 3.14159f;

RigidBody::RigidBody(Point pos, float m, int r) : dynamic(false), pos(pos),
								                  collisionRadius(r), 
												  mass(m), xVel(0), 
												  yVel(0), rot(0),
                                                  xForce(0), yForce(0) {
	lastUpdate = getTime();
}

void RigidBody::update() {
	// get time elapsed since last update
	long deltaT = getTime() - lastUpdate;
	lastUpdate = getTime();

	// update velocity
	xVel += xForce/mass * deltaT/1000.f;
	yVel += yForce/mass * deltaT/1000.f;

	// update position
	pos.x += xVel * deltaT/1000.f;
	pos.y += yVel * deltaT/1000.f;
	
	// clear forces
	xForce = 0;
	yForce = 0;
}

void RigidBody::applyForce(float xComponent, float yComponent) {
	xForce += xComponent;
	yForce += yComponent;
}

bool RigidBody::isDynamic() const{
	return dynamic;
}

void RigidBody::setDynamic(bool d) {
	dynamic = d;
}

Point RigidBody::getPos() const {
	return pos;
}

void RigidBody::setPos(Point p) {
	pos = p;
}

int RigidBody::getCollisionRadius() const { 
	return collisionRadius; 
}

void RigidBody::setCollisionRadius(int r) {
	collisionRadius = r; 
}

float RigidBody::getXVel() const {
	return xVel;
}

void RigidBody::setXVel(float v) {
	xVel = v;
}

float RigidBody::getYVel() const {
	return yVel;
}

void RigidBody::setYVel(float v) {
	yVel = v;
}

float RigidBody::getXForce() const {
	return xForce;
}

void RigidBody::setXForce(float f) {
	xForce = f;
}

float RigidBody::getYForce() const {
	return yForce;
}

void RigidBody::setYForce(float f) {
	yForce = f;
}

float RigidBody::getMass() {
	return mass;
}

void RigidBody::setMass(float m) {
	mass = m;
}

float RigidBody::getRot() {
	return rot;
}

void RigidBody::setRot(float r) {
	rot = r;
	// keep rotation between -pi and pi
	if(rot > PI) 
		rot -= 2*PI;
	if(rot < -PI) 
		rot += 2*PI;
}
