//
//  Bedroom.h
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofMain.h"
#include "Clock.h"
#include "ofxImageMask.h"
#include "ofxAVFVideoPlayer.h"

class Bedroom : public itg::ofxState<SharedData>
{
public:
	void setup();
    void update();
	void draw();
	string getName();
    void maskFrames( ofImage topLayer, ofImage mask, bool vidPlayerLoaded);
    void stateExit();
    
    ofColor myColor;
    
    ofImage wallOne;
    ofImage wallTwo;
    ofImage footer;
    
    Clock bedroomClock;
    
    ofxAVFVideoPlayer * vidPlayerOne;
    ofxAVFVideoPlayer * vidPlayerTwo;
    
    ofImage portraitMask;
    ofImage portraitFrames;
    
    ofImage windowMask;
    ofImage windowFrame;

};
