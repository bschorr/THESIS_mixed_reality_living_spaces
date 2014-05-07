//
//  transitionOne.cpp
//  THESIS_transitions
//
//  Created by Bernardo Santos Schorr on 5/2/14.
//
//

#include "transitionOne.h"

void transitionOne::setup() {

}

void transitionOne::draw() {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    int randomAdd = ofRandom(0, 5);
    
    for (int i = 0; i < randomAdd; i++) {
        Particle p;
        p.size = 0.0;
        p.vel = ofRandom(0.01, 0.1);
        p.pos.set(ofRandomWidth(), ofRandomHeight());
        p.alpha = ofRandom (1.0, 5.0);
        
        pList.push_back(p);
    }
    
    for (int i = 0; i < pList.size(); i++) {
        pList[i].size += pList[i].vel;
        ofSetColor(255, pList[i].alpha);
        ofPushMatrix(); {
            ofTranslate(pList[i].pos);
            ofRotate(45.0);
            ofCircle(0, 0, pList[i].size, pList[i].size);
        }ofPopMatrix();
    }
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    cout << pList.size() << endl;
    
}