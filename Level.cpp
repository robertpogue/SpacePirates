#include "Level.h"
#include "Color.h"
#include "Block.h"
#include "Gold.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Image.h"
#include "Platform.h"
#include "Point.h"
#include "Ship.h"

Level::Level() : gravity(-10) {
    
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
        if( position.x < 0 || position.x > size.x ||
            position.y < 0 || position.y > size.y) {
            ship.respawn();
        }
    }

}

void Level::draw(Graphics& graphics) {
    Point screenCenter{ graphics.screenWidth / 2, graphics.screenHeight / 2 };
    graphics.blit(background, screenCenter, 0);
    graphics.blit(level, screenCenter, 0);
    for(auto ship : ships) {
        graphics.draw(ship);
    }  
}

void Level::setLevel(Image i) {
    level = i;
    size = Point(i.getWidth(), i.getHeight());
}

void Level::setBackground(Image t) {
    background = t;
}

void Level::notify(Input::Event e) {
    for(auto& ship : ships) {
        ship.notify(e);
    }
}


