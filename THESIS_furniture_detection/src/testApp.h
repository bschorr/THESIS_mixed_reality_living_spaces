#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#define INPUTPIXELS 307200

class testApp : public ofBaseApp{

    struct numPixels{
        int first;
        int second;
    };
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void exit();
    
    //possible states of software
    bool bDrawBedroom;
    bool bDrawCinema;
    bool bDrawDining;
    bool bDrawLibrary;
    bool bDrawOffice;
    
    numPixels bedroomPix;
    numPixels cinemaPix;
    numPixels diningPix;
    numPixels libraryPix;
    numPixels officePix;
    
    
    //declaring the kinect
    ofxKinect kinect;
    void setKinect();
    
    //fancy openCV we'll be using
    ofxCvColorImage colorImg;
	ofxCvGrayscaleImage firstGrayThresh;
	ofxCvGrayscaleImage secondGrayThresh;
	ofxCvContourFinder firstContourFinder;
    ofxCvContourFinder secondContourFinder;
    void setOpenCv();
    void updateCv();
    void drawDebug();
    bool bDrawDebug;
    
    int firstNearThreshold;
	int firstFarThreshold;
    
	int secondNearThreshold;
	int secondFarThreshold;
    
    int blobMinSize, blobMaxSize;
    
    int lowArea, highArea;
    int lowBlobNum, highBlobNum;
    
    
    //for limiting area of blob tracking
    ofImage kinectPixels;
    ofVec2f cropOrigin;
    ofVec2f cropSize;
    
    //gui pointers and set function
    ofxUISuperCanvas *threshGui;
    ofxUISuperCanvas *cvGui;
    void guiEvent(ofxUIEventArgs &e);
    void setGui();
	
	int angle;
    
    numPixels incomingPix;
};
