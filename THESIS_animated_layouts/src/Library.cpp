//
//  Library.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Library.h"

void Library::setup()
{
    libraryClock.setup("library_clock");
    wallOne.loadImage("library/wallOne.png");
    wallTwo.loadImage("library/wallTwo.png");
    
    vidPlayer = new ofxAVFVideoPlayer;
    vidPlayer->loadMovie("library/videos/window4.mp4");
    //vidPlayer->loadMovie("library/videos/window3.mp4");
}

void Library::update()
{
    vidPlayer->update();
    
    if(true || vidPlayer->isLoaded()) {
        vidPlayer->play();
    }

}

void Library::draw()
{
    
    getSharedData().wallOne.begin();{
        wallOne.draw(0, 0);
        
    }getSharedData().wallOne.end();
    
    getSharedData().wallTwo.begin();{

        vidPlayer->draw(-70, -40, 1280, 720);
        //vidPlayer->draw(0, 0);
        wallTwo.draw(0, 0);
        libraryClock.draw(468, 210, 180, 180);

        
    }getSharedData().wallTwo.end();
}

string Library::getName()
{
	return "library";
}

void Library::stateExit() {
    vidPlayer->stop();
}
