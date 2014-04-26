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

class Bedroom : public itg::ofxState<SharedData>
{
public:
	void setup();
    void update();
	void draw();
	string getName();
    ofColor myColor;
    
    Clock bedroomClock;
};
