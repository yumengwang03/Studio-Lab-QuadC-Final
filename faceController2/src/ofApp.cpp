#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

ofSerial serial;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    
    cam.initGrabber(640, 480);
    
    serial.setup("/dev/tty.usbmodem1411", 9600);
    
    tracker.setup();
    
    w = ofGetWidth();
    h = ofGetHeight();
    ofSetWindowShape(w, h);
    
    borderSize = w/4;
    circleSize = quadSize = squareSize = triangleSize = 0;
    transformVel = 0;
    
    startX1 = borderSize/2;
    startX2 = borderSize*1.5;
    startX3 = borderSize*2.5;
    startX4 = borderSize*3.5;
    startY1 = startY2 = startY3 = startY4 = borderSize/2;
    //particles 1
    for (int i = 0; i<50; i++) {
        
        ball bouncingBall1;
        
        bouncingBall1.setup(startX1, startY1);
        ballList1.push_back(bouncingBall1);
    }
    
    //particles 2
    for (int i = 0; i<50; i++) {
        
        ball bouncingBall2;
        
        bouncingBall2.setup(startX2, startY2);
        ballList2.push_back(bouncingBall2);
    }
    
    //particles 3
    for (int i = 0; i<50; i++) {
        
        ball bouncingBall3;
        
        bouncingBall3.setup(startX3, startY3);
        ballList3.push_back(bouncingBall3);
    }
    
    //particles 4
    for (int i = 0; i<50; i++) {
        
        ball bouncingBall4;
        
        bouncingBall4.setup(startX4, startY4);
        ballList4.push_back(bouncingBall4);
    }

    
    //cameraL = w/2 - 320;
    cameraL = 3*borderSize - 50;
    cameraT = borderSize;
    //cameraW = 640;
    cameraW = -2*borderSize + 100;
    cameraH = borderSize + 74;
//    translateL = cameraL - 60;
//    translateT = borderSize;
    
    mouth.loadImage("mouth.png");
    eyes.loadImage("eyes.png");
    winner.loadImage("winner.png");
    loser.loadImage("loser.png");
    n1.loadImage("1.png");
    n2.loadImage("2.png");
    n3.loadImage("3.png");
    
    
    ofSetVerticalSync(true);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    
    //game timer
    startTime = ofGetElapsedTimeMillis();
    endTime = 30000;
    percentage = 0;
    
    //reset game object timer
    startTimeRed = startTimeWhite = startTimeGreen = startTimeYellow = startTimeMouth = startTimeEye = ofGetElapsedTimeMillis();
    
    endTimeRed = endTimeWhite = endTimeGreen = endTimeYellow = 4000;
    endTimeMouth = endTimeEye = 4000;
    
    mouthL = borderSize/2;
    mouthT = 3*borderSize/2;
    mouthW = 0;
    mouthH = 0;
    
    eyeL = w - borderSize/2;
    eyeT = 3*borderSize/2;
    eyeW = 0;
    eyeH = 0;
    
    rock.loadSound("rock.wav");
    laugh.loadSound("laugh.wav");
    win.loadSound("win.wav");
    lose.loadSound("lose.wav");
    blink.loadSound("blink.wav");
    beep.loadSound("beep.wav");
    button.loadSound("button.wav");
    //rock.setVolume(1);  // make the stretch sound quieter than NOM NOM NOM
    

    win.setLoop(false);
    lose.setLoop(false);
    //beep.setLoop(false);
    
    beep3 = false;
    beep2 = false;
    beep1 = false;
   
}


//--------------------------------------------------------------
int parseInt (string del, string str) {
    std::size_t found = str.find(del);
    int rv = atoi(str.c_str() + found + del.length());
    return (rv);
}

void ofApp::update(){

    
    cam.update();
    if(cam.isFrameNew()) {
        //face tracking
        tracker.update(toCv(cam));
        position = tracker.getPosition();
        scale = tracker.getScale();
        orientation = tracker.getOrientation();
        rotationMatrix = tracker.getRotationMatrix();
    }
    
    int ttl = 100; // read x chars max
    
    char ch;
    while ((ch=serial.readByte())>0 && ttl-->0 && ch != '\n') {
        staging += ch;
    }
    
    if (ch == '\n') { // if we are done, create string to print
        
        buttonRed = parseInt("red:", staging);
        buttonWhite = parseInt("white:", staging);
        buttonGreen = parseInt("green:", staging);
        buttonYellow = parseInt("yellow:", staging);
        staging = "";
        //cout<<buttonWhite<<endl;
        
        buttonClear();
        
        char buffer[300];
    }
    
    transformVel = ofMap(percentage, 0, 1, 0.2, 2.4);
    
    eyeReset();
    mouthReset();
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    // update the timer this frame
    float startTimer = ofGetElapsedTimeMillis() - startTime;
    bool startTimesUp = false;
    
    
    if(startTimer >= 2000 && !startTimesUp) {
        startTimesUp = true;
   //}
    
    ofBackground(0);
    
    drawBorders();
    
    setTimer();
    
    resetGameObject();
    
    //camera face tracking
    ofSetColor(255);
    cam.draw(cameraL, cameraT, cameraW, cameraH);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);

    
    if(tracker.getFound()) {
        ofSetLineWidth(1);
        ofSetColor(255);
        //tracker.draw();
    
        ofSetupScreenOrtho(640, 480, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
//        ofTranslate(translateL, translateT);
//        applyMatrix(rotationMatrix);
//        ofScale(4,4,4);
//        ofDrawAxis(scale);
//        tracker.getObjectMesh().drawWireframe();
        
        //mouth points
        ofFill();
        ofSetColor(255, 153, 60);
        
        mouthPos1.x = tracker.getObjectPoint(48).x;
        mouthPos1.y = tracker.getObjectPoint(48).y;
        mouthPos2.x = tracker.getObjectPoint(54).x;
        mouthPos2.y = tracker.getObjectPoint(54).y;
        
//        ofCircle(mouthPos1.x, mouthPos1.y, 1);
//        ofCircle(mouthPos2.x, mouthPos2.y, 1);
        
        //eyebrow points
        eyePos1.x = tracker.getObjectPoint(38).x;
        eyePos1.y = tracker.getObjectPoint(38).y;
        eyePos2.x = tracker.getObjectPoint(20).x;
        eyePos2.y = tracker.getObjectPoint(20).y;
        
//        ofCircle(eyePos1.x, eyePos1.y, 1);
//        ofCircle(eyePos2.x, eyePos2.y, 1);
        
        //using a for-loop to find the number of the points
//        for(int i = 20; i < 25; i ++) {
//        ofCircle(tracker.getObjectPoint(i).x, tracker.getObjectPoint(i).y, 1);
//        }
    }

    setTimer2();

    //winning
    if(timesUp && circleSize < borderSize && quadSize < borderSize && squareSize < borderSize && triangleSize < borderSize && mouthL > 0 && eyeL + eyeW < w) {
        winning = true;
    }
    //losing
    if(circleSize >= borderSize/2 || quadSize >= borderSize/2 || squareSize >= borderSize/2 || triangleSize >= borderSize/2 || mouthL <= 0 || eyeL + eyeW >= w) {
        losing = true;
    }
    
    drawWinScreen();
    drawGameOverScreen();
    }
}

//--------------------------------------------------------------
void ofApp::drawBorders(){
    //particles
    for (int i = 0; i < ballList1.size(); i++) {
        ballList1[i].update(circleSize, borderSize/2, borderSize/2);
    }
    
    for (int i = 0; i < ballList2.size(); i++) {
        ballList2[i].update(quadSize, borderSize*1.5, borderSize/2);
    }
    
    for (int i = 0; i < ballList3.size(); i++) {
        ballList3[i].update(squareSize, borderSize*2.5, borderSize/2);
    }
    
    for (int i = 0; i < ballList4.size(); i++) {
        ballList4[i].update(triangleSize, borderSize*3.5, borderSize/2);
    }
    
    ofNoFill();
    
    //draw particles
    if (ballList1.size() > 3) {
        for (int i = 2; i < ballList1.size(); i++) {
            ofVec2f posOne = ballList1[i].pos;
            ofVec2f posTwo = ballList1[i-1].pos;
            ofVec2f posThree;
            posThree.x = borderSize/2;
            posThree.y = borderSize/2;
            
            ofNoFill();
            ofSetColor(235, 0, 0);
            
            ofTriangle(posOne.x, posOne.y, posTwo.x, posTwo.y, posThree.x, posThree.y);
            
        }
    }
    
    if (ballList2.size() > 3) {
        for (int i = 2; i < ballList2.size(); i++) {
            ofVec2f posOne = ballList2[i].pos;
            ofVec2f posTwo = ballList2[i-1].pos;
            ofVec2f posThree;
            posThree.x = borderSize*1.5;
            posThree.y = borderSize/2;
            ofNoFill();
            ofSetColor(255);
            
            ofTriangle(posOne.x, posOne.y, posTwo.x, posTwo.y, posThree.x, posThree.y);
            
        }
    }
    
    
    if (ballList3.size() > 3) {
        for (int i = 2; i < ballList3.size(); i++) {
            ofVec2f posOne = ballList3[i].pos;
            ofVec2f posTwo = ballList3[i-1].pos;
            ofVec2f posThree;
            posThree.x = borderSize*2.5;
            posThree.y = borderSize/2;
            ofNoFill();
            ofSetColor(40, 255, 40);
            
            ofTriangle(posOne.x, posOne.y, posTwo.x, posTwo.y, posThree.x, posThree.y);
            
        }
    }
    
    
    if (ballList4.size() > 3) {
        for (int i = 2; i < ballList4.size(); i++) {
            ofVec2f posOne = ballList4[i].pos;
            ofVec2f posTwo = ballList4[i-1].pos;
            ofVec2f posThree;
            posThree.x = borderSize*3.5;
            posThree.y = borderSize/2;
            
            ofNoFill();
            ofSetColor(240, 240, 0);
            
            ofTriangle(posOne.x, posOne.y, posTwo.x, posTwo.y, posThree.x, posThree.y);
            
        }
    }
    
    ofNoFill();
    
    //1:circle
    ofSetColor(120);
    ofRect(0,0,borderSize,borderSize);
    
//    ofSetColor(255);
//    ofSetCircleResolution(100);
//    ofCircle(borderSize/2, borderSize/2, circleSize/2);
    
    //2:Quad
    ofSetColor(120);
    ofRect(borderSize,0,borderSize,borderSize);
    
//    ofSetColor(0);
//    ofBeginShape();
//    ofVertex(borderSize*3/2, borderSize/2 - quadSize/2);
//    ofVertex(borderSize*3/2 + quadSize/2, borderSize/2);
//    ofVertex(borderSize*3/2, borderSize/2 + quadSize/2);
//    ofVertex(borderSize*3/2 - quadSize/2, borderSize/2);
//    ofEndShape();
    
    //3:square
    ofSetColor(120);
    ofRect(borderSize*2,0,borderSize,borderSize);
    
//    ofSetColor(0);
//    ofRect(borderSize*5/2 - squareSize/2, borderSize/2 - squareSize/2, squareSize, squareSize);
    
    //4:triangle
    ofSetColor(120);
    ofRect(borderSize*3,0,borderSize,borderSize);
    
//    ofSetColor(0);
//    ofBeginShape();
//    ofVertex(borderSize*7/2, borderSize/2);
//    ofVertex(borderSize*7/2 - triangleSize/2, borderSize/2 - triangleSize/2);
//    ofVertex(borderSize*7/2 + triangleSize/2, borderSize/2 - triangleSize/2);
//    ofEndShape();
//    ofBeginShape();
//    ofVertex(borderSize*7/2, borderSize/2);
//    ofVertex(borderSize*7/2 - triangleSize/2, borderSize/2 + triangleSize/2);
//    ofVertex(borderSize*7/2 + triangleSize/2, borderSize/2 + triangleSize/2);
//    ofEndShape();
    
    //set mouth border
//    ofSetColor(255, 100, 100);
    ofRect(0, borderSize, borderSize, borderSize);
    //draw mouth
    ofSetColor(255);
    mouth.draw(mouthL, mouthT, mouthW, mouthH);
    
    //set the eyes border
//    ofSetColor(255, 200, 100);
    ofSetColor(120);
    ofRect(w - borderSize, borderSize, borderSize, borderSize);
    //draw eyes
    ofSetColor(255);
    eyes.draw(eyeL, eyeT, eyeW, eyeH);
}

void ofApp::resetGameObject(){
    setTimerRed();
    
    //circle
    if (timesUpRed && circleSize < borderSize) {
        circleSize += transformVel;
    }

    setTimerWhite();

    //quad
    if (timesUpWhite && quadSize < borderSize) {
        quadSize += transformVel;
    }
    
    setTimerGreen();
    
    //square
    if (timesUpGreen && squareSize < borderSize) {
        squareSize += transformVel;
    
    }
    
    setTimerYellow();
    
    //triangles
    if (timesUpYellow && triangleSize < borderSize) {
        triangleSize += transformVel;
    }
    
    setTimerMouth();
    
    if (timesUpMouth && mouthL > 0) {
        mouthL -= transformVel/2;
        mouthT -= transformVel/2;
        mouthW += transformVel;
        mouthH += transformVel;
    }
    
    setTimerEye();
    
    if (timesUpEye && eyeW < borderSize) {
        eyeL -= transformVel/2;
        eyeT -= transformVel/2;
        eyeW += transformVel;
        eyeH += transformVel;
    }
}

//--------------------------------------------------------------
void ofApp::drawGameOverScreen() {
    if(losing && !winning) {
       
        if (!lose.getIsPlaying() && !win.getIsPlaying()) {
            lose.play();
        }
        
//        cameraL = ofClamp(cameraL, 0, w);
//        cameraT = ofClamp(cameraT, 0, borderSize);
//        cameraW = ofClamp(cameraW, 0, w);
//        cameraH = ofClamp(cameraH, 0, h);
//        
//        cameraL -= 6;
//        cameraT -= 6;
//        cameraW += 12;
//        cameraH += 6;
        
//        ofSetColor(0);
//        ofRect(0,0, 75,h);
//        ofRect(w-75,0, 75,h);
        
//        for (int i=0; i<finder.size(); i++) {
//            ofRectangle r = finder.getObject(0);
//            //ofRectangle(r.x, r.y, r.width, r.height);
//            
//            loser.draw(r.x, r.y, r.width, r.height);
//        }
        ofSetColor(255);
        loser.draw(200, 300, 240, 120);
    }
}

//--------------------------------------------------------------
void ofApp::drawWinScreen() {
    if(winning && !losing) {
        
        if (!win.getIsPlaying() && !lose.getIsPlaying()) {
            win.play();
        }
        
//        cameraL = ofClamp(cameraL, 0, w-300);
//        cameraT = ofClamp(cameraT, 0, borderSize);
//        cameraW = ofClamp(cameraW, 0, w-300);
//        cameraH = ofClamp(cameraH, 0, h);
//        
//        cameraL += 6;
//        cameraT -= 6;
//        cameraW -= 6;
//        cameraH += 6;
//        
//        ofSetColor(0);
//        ofRect(0,0, 150,h);
//        ofRect(w-150,0, 150,h);
        
        //for (int i=0; i<finder.size(); i++) {
         //   ofRectangle r = finder.getObject(0);
            //ofRectangle(r.x, r.y, r.width, r.height);
            
            //winner.draw(r.x, r.y, r.width, r.height);
        //}
        
        ofSetColor(255);
        winner.draw(180, 300, 240, 120);
    }
}


//--------------------------------------------------------------
void ofApp::setTimer() {
    float barWidth = w;
    
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    
    if(timer >= endTime && !timesUp) {
        timesUp = true;
    }
    
    // the background of the progress bar
    ofFill();
    ofSetColor(100);
    ofRect(0, ofGetHeight()-30, barWidth, 30);
    
    // get the percentage of the timer
    percentage = ofMap(timer, 3000, endTime, 0.0, 1.0, true);
    ofSetColor(255);
    ofRect(0, ofGetHeight()-30, barWidth*percentage, 30);
    
    // draw the percantage
    ofSetColor(20);
    ofDrawBitmapString(ofToString(percentage*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/4)+20);
    
}

//--------------------------------------------------------------
void ofApp::setTimer2() {
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    //countdown to be ready
    if(timer >= 2000 && timer < 3000 && !timesUp) {
        //3
        
        if(!beep3) {
        beep3 = true;
        beep.setLoop(false);
        beep.play();
        }
        
        ofSetColor(255);
        ofRect(0, 0, w, h);
        n3.draw(260, 130, 120, 200);
//        cout<<w<<endl;
//        cout<<h<<endl;
    }
    
    if(timer >= 3000 && timer < 4000 && !timesUp) {
        //2
        if (!beep2) {
            beep2  = true;
            beep.setLoop(false);
            beep.play();
        }
        ofSetColor(170);
        ofRect(0, 0, w, h);
        n2.draw(260, 130, 120, 200);
//        cout<<w<<endl;
//        cout<<h<<endl;
    }
    if(timer >= 4000 && timer < 5000 && !timesUp) {
        //1
        if (!beep1) {
        beep1  = true;
        beep.setLoop(false);
        beep.play();
    }
        ofSetColor(80);
        ofRect(0, 0, w, h);
        
        n1.draw(260, 130, 120, 200);
//        cout<<w<<endl;
//        cout<<h<<endl;
    }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'q') {
        circleSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList1.size(); i++) {
            ballList1[i].reset(startX1, startY1);
        }
        startTimeRed = ofGetElapsedTimeMillis();
        timesUpRed = false;
//        endTimeRed -= ofRandom(-endTimeRed, endTimeRed);
        endTimeRed = ofRandom(500, 3000);
        setTimerRed();
    } else if(key == 'w') {
        quadSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList2.size(); i++) {
            ballList2[i].reset(startX2, startY2);
        }
        startTimeWhite = ofGetElapsedTimeMillis();
        timesUpWhite = false;
//      endTimeWhite -= ofRandom(-endTimeWhite, endTimeWhite);
        endTimeWhite = ofRandom(500, 3000);
        setTimerWhite();
    } else if(key == 'e') {
        squareSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList3.size(); i++) {
            ballList3[i].reset(startX3, startY3);
        }
        startTimeGreen = ofGetElapsedTimeMillis();
        timesUpGreen = false;
//        endTimeGreen -= ofRandom(-endTimeGreen, endTimeGreen);
        endTimeGreen = ofRandom(500, 3000);
        setTimerGreen();
    } else if(key == 'r') {
        triangleSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList4.size(); i++) {
            ballList4[i].reset(startX4, startY4);
        }
        startTimeYellow = ofGetElapsedTimeMillis();
        timesUpYellow = false;
//        endTimeYellow -= ofRandom(-endTimeYellow, endTimeYellow);
        endTimeYellow = ofRandom(500, 3000);
        setTimerYellow();
    }
    
}

//--------------------------------------------------------------
void ofApp::setTimerRed() {
    timesUpRed = false;

    float timer = ofGetElapsedTimeMillis() - startTimeRed;
    
    if(timer >= endTimeRed && !timesUpRed) {
        timesUpRed = true;
    }
}

//--------------------------------------------------------------
void ofApp::setTimerWhite() {
    timesUpWhite = false;
    
    float timer = ofGetElapsedTimeMillis() - startTimeWhite;
    
    if(timer >= endTimeWhite && !timesUpWhite) {
        timesUpWhite = true;
    }
}

//--------------------------------------------------------------
void ofApp::setTimerGreen() {
    timesUpGreen = false;
    
    float timer = ofGetElapsedTimeMillis() - startTimeGreen;
    
    if(timer >= endTimeGreen && !timesUpGreen) {
        timesUpGreen = true;
    }
}

//--------------------------------------------------------------
void ofApp::setTimerYellow() {
    timesUpYellow = false;
    
    float timer = ofGetElapsedTimeMillis() - startTimeYellow;
    
    if(timer >= endTimeYellow && !timesUpYellow) {
        timesUpYellow = true;
    }
}

//--------------------------------------------------------------
void ofApp::setTimerMouth() {
    timesUpMouth = false;
    
    float timer = ofGetElapsedTimeMillis() - startTimeMouth;
    
    if(timer >= endTimeMouth && !timesUpMouth) {
        timesUpMouth = true;
    }
}

//--------------------------------------------------------------
void ofApp::setTimerEye() {
    timesUpEye = false;
    
    float timer = ofGetElapsedTimeMillis() - startTimeEye;
    
    if(timer >= endTimeEye && !timesUpEye) {
        timesUpEye = true;
    }
}

//--------------------------------------------------------------
void ofApp::buttonClear() {
    
    if(buttonRed == 1) {
        circleSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList1.size(); i++) {
            ballList1[i].reset(startX1, startY1);
        }
        startTimeRed = ofGetElapsedTimeMillis();
        timesUpRed = false;
        //endTimeRed = ofClamp(endTimeRed,1000, 7000);
        //endTimeRed -= ofRandom(-endTimeRed, endTimeRed);
        endTimeRed = ofRandom(500, 3000);
        setTimerRed();
    } else if(buttonWhite == 1) {
        quadSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList2.size(); i++) {
            ballList2[i].reset(startX2, startY2);
        }
        startX2 = borderSize*1.5;
        startY2 = borderSize/2;
        startTimeWhite = ofGetElapsedTimeMillis();
        timesUpWhite = false;
//        endTimeWhite = ofClamp(endTimeWhite, 1000, 7000);
//        endTimeWhite -= ofRandom(-endTimeWhite, endTimeWhite);
        endTimeRed = ofRandom(500, 3000);
        setTimerWhite();
    } else if(buttonGreen == 1) {
        squareSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList3.size(); i++) {
            ballList3[i].reset(startX3, startY3);
        }
        startTimeGreen = ofGetElapsedTimeMillis();
        timesUpGreen = false;
//        endTimeGreen = ofClamp(endTimeGreen, 1000, 7000);
//        endTimeGreen -= ofRandom(-endTimeGreen, endTimeGreen);
        endTimeRed = ofRandom(500, 3000);
        setTimerGreen();
    } else if(buttonYellow == 1) {
        triangleSize = 0;
        if(!button.getIsPlaying()) {
            button.play();
        }
        for (int i = 0; i < ballList4.size(); i++) {
            ballList4[i].reset(startX4, startY4);
        }
        startTimeYellow = ofGetElapsedTimeMillis();
        timesUpYellow = false;
//        endTimeYellow = ofClamp(endTimeYellow, 1000, 7000);
//        endTimeYellow -= ofRandom(-endTimeYellow, endTimeYellow);
        endTimeRed = ofRandom(500, 3000);
        setTimerYellow();
    }
}

//--------------------------------------------------------------
void ofApp::mouthReset() {
    
    float mouthDist = mouthPos2.x - mouthPos1.x;
    //cout<<mouthDist<<endl;
    if (mouthDist >= 16.5) {
        if(!laugh.getIsPlaying()) {
        laugh.play();
        }
        mouthL = borderSize/2;
        mouthT = 3*borderSize/2;
        mouthW = 0;
        mouthH = 0;
        
        startTimeMouth = ofGetElapsedTimeMillis();
        timesUpMouth = false;
        endTimeMouth = ofClamp(endTimeMouth, 3000, 7000);
        endTimeMouth -= ofRandom(-endTimeMouth, endTimeMouth);
        setTimerMouth();
    }
}

//--------------------------------------------------------------
void ofApp::eyeReset() {
    
    float eyeDist = eyePos1.y - eyePos2.y;
    cout<<eyeDist<<endl;
    if(eyeDist >= 8) {
        if(!blink.getIsPlaying()) {
        blink.play();
        }
        eyeL = w - borderSize/2;
        eyeT = 3*borderSize/2;
        eyeW = 0;
        eyeH = 0;
        
        startTimeEye = ofGetElapsedTimeMillis();
        timesUpEye = false;
        endTimeEye = ofClamp(endTimeEye, 3000, 7000);
        endTimeEye -= ofRandom(-endTimeEye, endTimeEye);
        setTimerEye();
    }
}


