

#include "ball.h"

void ball::setup(float _posX, float _posY) {
    pos.x = _posX;
    pos.y = _posY;
    
//    pos.x = ofRandom(0, ofGetWidth());
//    pos.y = ofRandom(0, ofGetHeight());;
    
    vel.x = ofRandom(-3, 3);
    vel.y = ofRandom(-3, 3);
    
}

void ball::update(float radius, float centerX, float centerY) {

    pos += vel;
    
    float distance = ofDist(pos.x, pos.y, centerX, centerY);
    
    if(distance >= radius) {
        distance = radius;
        vel *= -1;
    }
}

void ball::draw() {
    
    ofCircle(pos, 0);
    
}

void ball::reset(float _posX, float _posY) {
    
    pos.x = _posX;
    pos.y = _posY;
    
    vel.x = ofRandom(-3, 3);
    vel.y = ofRandom(-3, 3);
    
}