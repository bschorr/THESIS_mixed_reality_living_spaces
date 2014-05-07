//
//  transitionOne.h
//  THESIS_transitions
//
//  Created by Bernardo Santos Schorr on 5/2/14.
//
//

#pragma once

#include "ofMain.h"

class transitionOne {
public:
    
    void setup();
    void draw();
    
    struct Particle {
        float size;
        float vel;
        ofVec2f pos;
        float alpha;
    };
    
    vector <Particle> pList;
    
};
