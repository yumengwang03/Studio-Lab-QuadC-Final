//
//  particle.h
//  faceController2
//
//  Created by wang yumeng on 5/10/15.
//
//

#pragma once

#include "ofMain.h"

class Particle {
public:
    
    Particle(ofVec2f _pos, ofVec2f _vel);
    
    void setup();
    
    void resetForces();
    void applyForce(ofVec2f force);
    void applyDampingForce(float damping);
    
    void update();
    void draw(ofColor _color);
    
    ofVec2f pos, vel, acc;
    
};


