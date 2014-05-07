//
//  Cinema.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Cinema.h"

void Cinema::setup() {
    
    wallOne.loadImage("cinema/wallOne.png");
    wallTwo.loadImage("cinema/wallTwo.png");
    
    vidPlayer = new ofxAVFVideoPlayer();
    vidPlayer->loadMovie("cinema/casablanca.mp4");
    //vidPlayer->loadMovie("library/videos/window3.mp4");
}

void Cinema::update()
{
    vidPlayer->update();
    
    if(true || vidPlayer->isLoaded()) {
        vidPlayer->play();
    }

}

void Cinema::draw()
{

    getSharedData().wallOne.begin();{
        vidPlayer->draw(130, 160);
        wallOne.draw(0, 0);
        
    }getSharedData().wallOne.end();
    
    getSharedData().wallTwo.begin();{
        
        wallTwo.draw(0, 0);
        
    }getSharedData().wallTwo.end();
    
}

string Cinema::getName()
{
	return "cinema";
}

void Cinema::stateExit() {
    vidPlayer->stop();
    getSharedData().isTransition = true;
}