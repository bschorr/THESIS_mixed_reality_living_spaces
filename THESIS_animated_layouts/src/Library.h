//
//  Library.h
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

class Library : public itg::ofxState<SharedData>
{
public:
    void setup();
	void update();
	void draw();
	string getName();
    void stateExit();
    
    Clock libraryClock;
    ofImage wallOne;
    ofImage wallTwo;
    
    ofxAVFVideoPlayer * vidPlayer;
    
};
