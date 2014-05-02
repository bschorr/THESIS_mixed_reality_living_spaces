//
//  Bedroom.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Bedroom.h"

void Bedroom::setup()
{
    bedroomClock.setup( "bedroom_clock" );
    wallOne.loadImage("bedroom/wallOne3.png");
    wallTwo.loadImage("bedroom/wallTwo2.png");
    footer.loadImage("bedroom/footer.png");
    portraitFrames.loadImage("bedroom/portraitFrames_2.png");
    
	portraitMask.loadImage("bedroom/portraitMask.png");
    windowMask.loadImage("bedroom/windowMask.png");
    windowFrame.loadImage("bedroom/windowFrame3.png");
    
    vidPlayerOne = new ofxAVFVideoPlayer();
    vidPlayerOne->loadMovie("bedroom/videos/bedroom_wallOne.mp4");
    
    vidPlayerTwo = new ofxAVFVideoPlayer();
    vidPlayerTwo->loadMovie("bedroom/videos/sunrise6.mp4");
    
    
    
}

void Bedroom::update()
{
    int i=0;
    
    vidPlayerOne->update();
    vidPlayerTwo->update();

    if(true || vidPlayerOne->isLoaded()) {
        vidPlayerOne->play();
    }
    
    if(true || vidPlayerTwo->isLoaded()) {
        vidPlayerTwo->play();
    }
    
}

void Bedroom::draw()
{
    
    getSharedData().wallOne.begin();{
        ofClear(255, 0, 0, 0);
        vidPlayerOne->draw(0, 0);
        
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetColor(150, 75, 0, 30);
        ofRect(0, 0, 935, 800);
        ofEnableAlphaBlending();
        
        ofSetColor(255);
        //getSharedData().maskFrames(wallOne, portraitMask, vidPlayerOne->isLoaded());
        wallOne.draw(0, 0);
        portraitFrames.draw(375, 116);
        footer.draw(-12, 743);
        bedroomClock.draw(150, 150, 200, 200);
        
    }getSharedData().wallOne.end();
    
    getSharedData().wallTwo.begin();{
        
        ofClear(255, 0, 0, 0);
        vidPlayerTwo->draw(-100, 0);
        wallTwo.draw(0, 0);
        windowFrame.draw(133, 79);
        footer.draw(-12, 743);
        
    }getSharedData().wallTwo.end();
}

string Bedroom::getName()
{
	return "bedroom";
}


void Bedroom::stateExit() {
    vidPlayerOne->stop();
    vidPlayerTwo->stop();
}
