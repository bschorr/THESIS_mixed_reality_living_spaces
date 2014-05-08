//
//  transitionOne.cpp
//  THESIS_transitions
//
//  Created by Bernardo Santos Schorr on 5/2/14.
//
//

#include "transitionOne.h"

void transitionOne::setup( itg::ofxStateMachine<SharedData> * _stateMachine ) {
    
    fbo.allocate(1870, 800, GL_RGBA);
    
    counter = 0;
    
    fbo.begin();
        ofClear(0, 0);
        ofBackground(0);
    fbo.end();
    
    stateMachine = _stateMachine;

}

void transitionOne::update() {
    
    fbo.begin();
    ofBackground(0);
    
    ofEnableAlphaBlending();
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    int randomAdd = ofRandom(0, 5);
    
    for (int i = 0; i < randomAdd; i++) {
        Particle p;
        p.size = 0.0;
        p.vel = ofRandom(0.5, 2.0);
        p.pos.set(ofRandom(1870), ofRandom(800));
        p.alpha = ofRandom (2.0, 7.0);
       
        pList.push_back(p);
    }
    
    for (int i = 0; i < pList.size(); i++) {
        pList[i].size += pList[i].vel;
        ofSetColor(255, pList[i].alpha);
        ofPushMatrix(); {
            ofTranslate(pList[i].pos);
            ofRotate(45.0);
            ofRect(0, 0, pList[i].size, pList[i].size);
        }ofPopMatrix();
    }
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofDisableAlphaBlending();
    fbo.end();
    
    counter++;
    
    if (counter > 300) {
        counter = 0;
        pList.clear();
        stateMachine->getSharedData().isTransition = false;
        fbo.begin();
        ofBackground(0);
        fbo.end();
    }
    
}

void transitionOne::draw() {
    
    ofSetColor(255);
    fbo.draw(0, 0);
    
}