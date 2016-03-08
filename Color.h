#pragma once

struct Color {
	int r, g, b; // 0-255
	Color(int R, int G, int B) : r(R), g(G), b(B) { };
    float rNorm() {return r/255.0f;} // normalized to 0-1 color range 
    float gNorm() {return g/255.0f;}
    float bNorm() {return b/255.0f;}
    friend extern bool operator==(const Color& c1, const Color& c2);
    friend extern bool operator!=(const Color& c1, const Color& c2);
};