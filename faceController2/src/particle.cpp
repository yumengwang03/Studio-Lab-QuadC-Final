//
//  particle.cpp
//  faceController2
//
//  Created by wang yumeng on 5/10/15.
//
//

#include "particle.h"

Particle::Particle(ofVec2f _pos, ofVec2f _vel) {
    pos.set(_pos);
    vel.set(_vel);
    //vel.x = ofRandom(-2, 2);
    //vel.y = ofRandom(-1, -5);
}

void Particle::setup() {
    
}

void Particle::resetForces() {
    acc *= 0;
}

void Particle::applyForce(ofVec2f force) {
    acc += force;
}

void Particle::applyDampingForce(float damping) {
    acc -= vel * damping;
}

void Particle::update() {
    vel += acc;
    pos += vel;
    
}

void Particle::draw(ofColor _color) {
    ofSetColor(_color);
}

