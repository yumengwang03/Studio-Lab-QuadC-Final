

#pragma once

#include "ofMain.h"

class ball {
    
public:
    void setup(float _posX, float _posY);
    void update(float radius, float centerX, float centerY);
    void draw();
    void reset(float _posX, float _posY);
    
    ofVec2f pos, vel;

    
};
