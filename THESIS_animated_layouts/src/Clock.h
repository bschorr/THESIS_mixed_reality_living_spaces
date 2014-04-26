//
//  Clock.h
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/25/14.
//
//

#pragma once

#include "ofMain.h"

class Clock {
public:
    void setup( string folder );
    void update();
    void draw( int x, int y, int w, int h );
    
    ofImage bkg;
    ofImage hours;
    ofImage minutes;
    ofImage seconds;
    
};

class PendulumClock : public Clock {
public:
    void setup( string folder );
    void update();
    void draw ( int x, int y, int w, int h );
    
    ofImage pendulumBkg;
    ofImage pendulum;
};