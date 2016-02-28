#pragma once
#include <vector>
#include "Point.h"

class RigidBody {
public:
	RigidBody(Point, float Mass=10, int Radius=7);

	virtual void update(int delta); // simulate physics
	virtual void onCollision(const RigidBody& other) { };

	void  applyForce(float xComponent,  // kg*px/s/s
		             float yComponent); // kg*px/s/s
	bool  isDynamic() const;
	void  setDynamic(bool);
	Point getPosition() const;
	void  setPosition(Point);
	int   getCollisionRadius() const;
	void  setCollisionRadius(int r);
	float getXForce() const;
	void  setXForce(float);
	float getYForce() const;
	void  setYForce(float);
	float getXVel() const;
	void  setXVel(float);
	float getYVel() const;
	void  setYVel(float);
	float getMass();
	void  setMass(float);
	float getRotation();
	void  setRotation(float);
private:
    bool  dynamic;
    Point pos;               // center of mass
    int   collisionRadius;
    float xForce;
    float yForce;
    float xVel;
    float yVel;
    float mass;
    float rot;
};

// determines if two rigidbodies are collding
// has no side-effects
bool areColliding(RigidBody const* const, RigidBody const* const);