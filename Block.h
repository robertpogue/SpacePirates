#pragma once

#include "Color.h"
#include "GameObject.h"
#include "Point.h"

class Block : public GameObject {
public:
	Block(Point p);
	void draw();
	Color color;
	const static int size = 10; // px
};
