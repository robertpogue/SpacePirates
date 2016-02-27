#pragma once

#include "Point.h"

class RigidBody {
	bool dynamic;
	Point pos;
	int collisionRadius;
	float xForce;
	float yForce;
	float xVel;
	float yVel;
	float mass;
	float rot;
public:
	RigidBody(Point, float Mass=10, int Radius=7);
	virtual void update(int delta); // simulate physics
	virtual void onCollision(const RigidBody& other) { };

	void applyForce(float xComponent, // kg*px/s/s
		            float yComponent);
	
	float getSpeedRelativeTo(const RigidBody&);

	// getters and setters
	bool isDynamic() const;
	void setDynamic(bool);
	Point getPos() const;
	void setPos(Point);
	int getCollisionRadius() const;
	void setCollisionRadius(int r);
	float getXForce() const;
	void setXForce(float);
	float getYForce() const;
	void setYForce(float);
	float getXVel() const;
	void setXVel(float);
	float getYVel() const;
	void setYVel(float);
	float getMass();
	void setMass(float);
	float getRot();
	void setRot(float);
};
