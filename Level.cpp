#include "Level.h"
#include "Color.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Image.h"
#include "Point.h"
#include "Ship.h"

Level::Level() 
    : gravity(-10),
    levelHeightPx(0),
    levelWidthPx(0) {
    
}
void Level::add(Ship ship) {
    ships.push_back(ship);
}

void Level::update(int delta) {
    for(auto& ship : ships) {
        // apply gravity
        float gravityForce = gravity * ship.getMass();
        ship.applyForce(0.f, gravityForce);

        // allow object to update
        ship.update(delta);
        
        // keep ship within level bounds
        Point position = ship.getPosition();
        if( position.x < 0 || position.x > levelWidthPx ||
            position.y < 0 || position.y > levelHeightPx) {
            ship.respawn();
        }

        // collide with level
        for(auto& ship : ships) {
            for(auto point : ship.collisionPoints) {
                point.rotateAboutOrigin(ship.getRotation()); // rotate with ship
                point = point + ship.getPosition(); // to world space
                Color c = level.getPixel(point);
                const Color transparent(255, 0, 255);
                if(c != transparent) {
                    float forceMultiplier = 1;
                    ship.applyForce(-ship.getXVel() * forceMultiplier,
                                    -ship.getYVel() * forceMultiplier);
                }
            }
        }
    }

}

void Level::draw(Graphics& graphics) {
    Point screenCenter{ graphics.screenWidth / 2, graphics.screenHeight / 2 };
    graphics.draw(background);
    graphics.draw(level);
    for(const auto& ship : ships) {
        graphics.draw(ship);
    }
}

void Level::setLevel(Image i) {
    level = i;
    levelWidthPx = i.getWidth();
    levelHeightPx = i.getHeight();
}

void Level::setBackground(Image t) {
    background = t;
}

void Level::notify(Input::Event e) {
    for(auto& ship : ships) {
        ship.notify(e);
    }
}

