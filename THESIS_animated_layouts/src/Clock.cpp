//
//  Clock.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/25/14.
//
//

#include "Clock.h"

void Clock::setup( string folder ) {
    
    bkg.loadImage( folder + "/background.png" );
    hours.loadImage( folder + "/hours.png" );
    minutes.loadImage( folder + "/minutes.png" );
    seconds.loadImage( folder + "/seconds.png" );
    
}

void Clock::draw(int x, int y, int w, int h) {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(x, y);

    bkg.draw(0, 0, w, h);
    
        ofPushMatrix();
            float hRot = ofMap(ofGetHours(), 0, 12, 0, 360);
            hRot += ofMap(ofGetMinutes(), 0, 60, 0, 30);
            ofRotate(hRot);
            hours.draw(0, 0, w, h);
        ofPopMatrix();
    
        ofPushMatrix();
            float mRot = ofMap(ofGetMinutes(), 0, 60, 0, 360);
            ofRotate(mRot);
            minutes.draw(0, 0, w, h);
        ofPopMatrix();
    
        ofPushMatrix();
            float sRot = ofMap(ofGetSeconds(), 0, 60, 0, 360);
            ofRotate(sRot);
            seconds.draw(0, 0, w, h);
        ofPopMatrix();
    
    ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
}

////----- Pendulum Clock from here on
void PendulumClock::setup( string folder ) {
    
    bkg.loadImage( folder + "/background.png" );
    hours.loadImage( folder + "/hours.png" );
    minutes.loadImage( folder + "/minutes.png" );
    
    pendulumBkg.loadImage( folder + "/pendulum_bkg.png" );
    pendulum.loadImage( folder + "/pendulum.png" );
    
}

void PendulumClock::update () {
    
}

void PendulumClock::draw(int x, int y, int w, int h) {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();{
    
        ofTranslate(x, y);
    
        ofPushMatrix();{
            ofTranslate(0, h*0.45);
            pendulumBkg.draw(0, 0, w, h);
            
            int pendPos = ofGetElapsedTimeMillis() % 2000;
            
            if (pendPos < 500) {
                float rotPos = sin(ofMap(pendPos, 0, 500, 0, HALF_PI)) * 20.0;
                ofRotate(rotPos);
            } else if (pendPos < 1000) {
                float rotPos = sin(ofMap(pendPos, 500, 1000, HALF_PI, 0)) * 20.0;
                ofRotate(rotPos);
            } else if (pendPos < 1500) {
                float rotPos = sin(ofMap(pendPos, 1000, 1500, 0, HALF_PI)) * -20.0;
                ofRotate(rotPos);
            } else if (pendPos < 2000) {
                float rotPos = sin(ofMap(pendPos, 1500, 2000, HALF_PI, 0)) * -20.0;
                ofRotate(rotPos);
            }
            ofTranslate(0, -h*0.05);
            pendulum.draw(0, 0, w, h);
        }ofPopMatrix();
        
        bkg.draw(0, 0, w, h);
        
        ofPushMatrix();
        float hRot = ofMap(ofGetHours(), 0, 12, 0, 360);
        hRot += ofMap(ofGetMinutes(), 0, 60, 0, 30);
        ofRotate(hRot);
        hours.draw(0, 0, w, h);
        ofPopMatrix();
        
        ofPushMatrix();
        float mRot = ofMap(ofGetMinutes(), 0, 60, 0, 360);
        ofRotate(mRot);
        minutes.draw(0, 0, w, h);
        ofPopMatrix();
    
    
    }ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
}
