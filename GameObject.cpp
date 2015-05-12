#include "GameObject.h"
#include "Point.h"
#include "RigidBody.h"

GameObject::GameObject() : RigidBody(Point()) {
}

GameObject::GameObject(Point p) : RigidBody(p) {
}
