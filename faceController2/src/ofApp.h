#pragma once

#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

#include "ofxFaceTracker.h"
#include "timer.h"
#include "ball.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawBorders();
    void resetGameObject();
    void drawGameOverScreen();
    void drawWinScreen();

    void setTimer();
    void setTimer2();
    void buttonClear();
    void setTimerRed();
    void setTimerWhite();
    void setTimerGreen();
    void setTimerYellow();
    void setTimerMouth();
    void setTimerEye();
    
    void mouthReset();
    void eyeReset();
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;
    
    Mat translation, rotation;
    ofMatrix4x4 pose;
    
    int w;
    int h;
    
    int cameraL;
    int cameraT;
    int cameraW;
    int cameraH;
    int translateL;
    int translateT;
    
    int borderSize;
    float circleSize;
    float quadSize;
    float squareSize;
    float triangleSize;
    
    float transformVel;
    
    float startX1;
    float startX2;
    float startX3;
    float startX4;
    float startY1;
    float startY2;
    float startY3;
    float startY4;
    
    ofImage mouth;
    ofImage eyes;
    ofImage winner;
    ofImage loser;
    
    ofImage n1;
    ofImage n2;
    ofImage n3;
    
    
    //game timer
    float startTime;
    float endTime;
    bool timesUp;
    float percentage;
    
    //reset game object timer
    float startTimeRed;
    float startTimeWhite;
    float startTimeGreen;
    float startTimeYellow;
    float startTimeMouth;
    float startTimeEye;
    
    float endTimeRed;
    float endTimeWhite;
    float endTimeGreen;
    float endTimeYellow;
    float endTimeMouth;
    float endTimeEye;
    
    bool timesUpRed;
    bool timesUpWhite;
    bool timesUpGreen;
    bool timesUpYellow;
    bool timesUpMouth;
    bool timesUpEye;
    
    string staging;
    
    //reading the button state
    int buttonRed = 0;
    int buttonWhite = 0;
    int buttonGreen = 0;
    int buttonYellow = 0;
    
    //mouth and eye position
    ofVec2f mouthPos1;
    ofVec2f mouthPos2;
    ofVec2f eyePos1;
    ofVec2f eyePos2;
    
    //eye and mouth
    float mouthL;
    float mouthT;
    float mouthW;
    float mouthH;
    
    float eyeL;
    float eyeT;
    float eyeW;
    float eyeH;
    
    ofxCv::ObjectFinder finder;
    
    bool winning = false;
    bool losing = false;
    
    vector<ball> ballList1;
    vector<ball> ballList2;
    vector<ball> ballList3;
    vector<ball> ballList4;
    
    ofSoundPlayer rock;
    ofSoundPlayer laugh;
    ofSoundPlayer blink;
    ofSoundPlayer win;
    ofSoundPlayer lose;
    ofSoundPlayer beep;
    ofSoundPlayer button;
    
    bool beep3;
    bool beep2;
    bool beep1;
    
    
};
