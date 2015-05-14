//
//  particleSystem.h
//  faceController2
//
//  Created by wang yumeng on 5/10/15.
//
//

#pragma once

#include "ofMain.h"
#include "particle.h"

class particleSystem {
public:
    
    particleSystem(ofVec2f _pos);
    void update(ofVec2f _force);
    void draw();
    
    void mouseDragged(float x, float y);
    
    vector<Particle> particleList;
    ofVec2f pos;
    
};