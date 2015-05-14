//
//  timer.cpp
//  faceController2
//
//  Created by wang yumeng on 4/26/15.
//
//

#include "timer.h"

timer::timer() {
    startTime = ofGetElapsedTimeMillis();
    timesUp = false;
    
//    for(int i = 0; i < 8; i++) {
//        timeList[i] = 12 + 4*i;
//        endTime = timeList[i];
//    }
    
    endTime = 10000;
}

void timer::update() {
    
}

void timer::draw() {
    float barWidth = 500;
    
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if(timer >= endTime && !timesUp) {
        timesUp = true;
    }
    
    // the background of the progress bar
    ofSetColor(100);
    ofRect((ofGetWidth()-barWidth)/2, ofGetHeight()/4, barWidth, 30);
    
    // get the percantage of the timer
    float percentage = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetHexColor(0x3ca9fc);
    ofRect((ofGetWidth()-barWidth)/2, ofGetHeight()/4, barWidth*percentage, 30);
    
    // draw the percantage
    ofSetColor(20);
    ofDrawBitmapString(ofToString(percentage*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/4)+20);


    
}

