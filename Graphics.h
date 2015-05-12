#pragma once

#include "Color.h"
#include "Point.h"
#include <string>

namespace Graphics {
	void startUp();
	void triangle(const Point& p1, 
		          const Point& p2, 
				  const Point& p3,
				  const Color& c);
    void writeText(std::string text, int xPos, int yPos);
	void flip();
	void shutDown();
    
    // colors
    static Color black(0,0,0);
    static Color red(255, 0, 0);
    static Color green(0, 255, 0);
    static Color blue(0, 0, 255);
    static Color darkBlue(5, 5, 40); // dark blue
    static Color yellow(255,255, 0);

}
