//
//  timer.h
//  faceController2
//
//  Created by wang yumeng on 4/26/15.
//
//

#ifndef __faceController2__timer__
#define __faceController2__timer__

#include <stdio.h>

#include "ofMain.h"


class timer {
public:
    timer();
    void update();
    void draw();
    void reset();
    
    float startTime;
    float endTime;
    int timeList[8];
    bool timesUp;
};


#endif /* defined(__faceController2__timer__) */
