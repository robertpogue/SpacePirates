#include "Color.h"

bool operator==(const Color& c1, const Color& c2) {
    if(c1.r == c2.r && c1.g == c2.g && c1.b == c2.b) return true;
    else return false;
}
bool operator!=(const Color& c1, const Color& c2) {
    return !(c1 == c2);
}
