//
//  dining.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Dining.h"

void Dining::setup() {
    
    diningClock.setup ("dining_clock");
    wallOne.loadImage("dining/wallOne.png");
    wallTwo.loadImage("dining/wallTwo.png");
    
    vidPlayer = new ofxAVFVideoPlayer;
    vidPlayer->loadMovie("dining/videos/garden3.mp4");
    //vidPlayer->loadMovie("dining/videos/garden2.mov");
}

void Dining::update()
{
    vidPlayer->update();
    
    if(true || vidPlayer->isLoaded()) {
        vidPlayer->play();
    }

}

void Dining::draw()
{
    getSharedData().wallOne.begin();{
        ofClear(255, 0, 0, 0);
        ofDrawBitmapString("Dining", 30, 30);
        //vidPlayer->draw(-360, 0, 1420, 800);
        vidPlayer->draw(0, 0);
        wallOne.draw(0, 0);
    }getSharedData().wallOne.end();
    
    getSharedData().wallTwo.begin();{
        ofClear(255, 0, 0, 0);
        wallTwo.draw(0, 0);
        diningClock.draw(474, 211, 180, 180);
    }getSharedData().wallTwo.end();
}

string Dining::getName()
{
	return "dining";
}

void Dining::stateExit() {
    vidPlayer->stop();
    getSharedData().isTransition = true;
}
