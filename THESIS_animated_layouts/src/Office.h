//
//  Office.h
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "Clock.h"
#include "ofxAVFVideoPlayer.h"

class Office : public itg::ofxState<SharedData>
{
public:
    void setup();
	void update();
	void draw();
	string getName();
    void stateExit();
    
    Clock officeClock;
    ofxAVFVideoPlayer *vidPlayer;
    
    ofImage wallOne;
    ofImage wallTwo;
    ofImage windowFrame;
    ofImage calendar;
    ofImage dashboard;
    ofImage footer;
    
    ofTrueTypeFont helvetica;
    
    int circleX, circleY;
    
    
};
