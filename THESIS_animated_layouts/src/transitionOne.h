//
//  transitionOne.h
//  THESIS_transitions
//
//  Created by Bernardo Santos Schorr on 5/2/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxStateMachine.h"
#include "SharedData.h"

class transitionOne {
public:
    
    void setup( itg::ofxStateMachine<SharedData> * _stateMachine );
    void update();
    void draw();
    
    struct Particle {
        float size;
        float vel;
        ofVec2f pos;
        float alpha;
    };
    
    vector <Particle> pList;
    ofFbo fbo;
    int counter;
    itg::ofxStateMachine<SharedData> * stateMachine;
    
};
