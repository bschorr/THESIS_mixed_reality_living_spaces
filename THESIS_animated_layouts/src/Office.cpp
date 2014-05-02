//
//  Office.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Office.h"

void Office::setup(){
    officeClock.setup("office_clock");
    
    vidPlayer = new ofxAVFVideoPlayer();
    vidPlayer->loadMovie("office/videos/officeWindow2.mp4");
    
    wallOne.loadImage("office/wallOne.png");
    wallTwo.loadImage("office/wallTwo2.png");
    
    windowFrame.loadImage("office/windowFrame.png");
    calendar.loadImage("office/calendar.png");
    dashboard.loadImage("office/dashboard.png");
    footer.loadImage("office/footer.png");
    
    
    //helvetica.loadFont("office/HelveticaNeueLTStd-Roman.otf", 10.0, false);
    helvetica.loadFont("office/HelveticaNeueLTStd-Lt.otf", 10.0, true);
    helvetica.setLineHeight(20.0);
    
    ofSetCircleResolution(30);
    
    circleX = 119;
    circleY = 158;
    
    int day = ofGetDay();
    int matrixPos = day + 3;
    
    int xPos = (matrixPos % 7) * 31;
    int yPos = floor(matrixPos/7) * 27;
    
    circleX += xPos;
    circleY += yPos;
    
}

void Office::update()
{
    int i=0;
    
    vidPlayer->update();
    
    if(true || vidPlayer->isLoaded()) {
        vidPlayer->play();
    }
    
}

void Office::draw()
{
    getSharedData().wallOne.begin();{
        
        vidPlayer->draw(71, 67);
        wallOne.draw(0, 0);
        windowFrame.draw(74, 72);
        footer.draw(-12, 743);
        
    }getSharedData().wallOne.end();
    
    getSharedData().wallTwo.begin();{
        wallTwo.draw(0, 0);
        officeClock.draw(770, 150, 200, 200);
        calendar.draw(90, 70);
        dashboard.draw(90, 300);
        
        ofFill();
        ofSetColor(60);
        
        std::stringstream str;
        
        str << "- Pick up the Laundry" << endl <<
        "- Call Associates about the deal" << endl <<
        "- Buy granola, fruit and cereal" << endl;
        
        helvetica.drawString(str.str(), 110, 341);
        ofNoFill();
        ofSetColor(0, 200, 255);
        ofEnableSmoothing();
        ofSetLineWidth(1.5);
        ofCircle(circleX, circleY, 12);
        ofSetColor(255);
        ofDisableSmoothing();
        footer.draw(-12, 743);
        ofFill();
        
    }getSharedData().wallTwo.end();

}

string Office::getName()
{
	return "office";
}

void Office::stateExit() {
    vidPlayer->stop();
}