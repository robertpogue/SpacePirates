#include "Block.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Point.h"

Block::Block(Point p) : GameObject(p), color(Graphics::black) {
	setCollisionRadius(5);
}

void Block::draw() {
	Point topRight = Point(getPos().x + size/2, getPos().y + size/2);
	Point topLeft = Point(getPos().x - size/2, getPos().y + size/2);
	Point bottomLeft = Point(getPos().x - size/2, getPos().y - size/2);
	Point bottomRight = Point(getPos().x + size/2, getPos().y - size/2);
	Graphics::triangle(topRight, topLeft, bottomLeft, color);
	Graphics::triangle(topRight, bottomLeft, bottomRight, color);
}
