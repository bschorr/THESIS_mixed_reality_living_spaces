#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

#define INPUTPIXELS 307200

class testApp : public ofBaseApp{

    struct cvBlob{
        int area;
        int index;
        int width;
        int height;
        ofVec2f pos;
        
        void reset() {
            area = 0;
            index = 0;
            width = 0;
            height = 0;
            pos.set(0, 0);
        }
    };
    
    struct numPixels {
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
        void resetCurrentRoom();
    
        void exit();
    
    //possible states of software
    bool bDrawBedroom;
    bool bDrawCinema;
    bool bDrawDining;
    bool bDrawLibrary;
    bool bDrawOffice;
    
    //declaring the kinect
    ofxKinect kinect;
    void setKinect();
    
    //fancy openCV we'll be using
    ofxCvColorImage colorImg;
	ofxCvGrayscaleImage lowGrayThresh;
	ofxCvGrayscaleImage highGrayThresh;
	ofxCvContourFinder lowContourFinder;
    ofxCvContourFinder highContourFinder;
    void setOpenCv();
    void updateCv();
    void drawDebug();
    bool bDrawDebug;
    
    int lowNearThreshold;
	int lowFarThreshold;
    
	int highNearThreshold;
	int highFarThreshold;
    
    int blobMinSize, blobMaxSize;
    
    int lowArea, highArea;
    int lowBlobNum, highBlobNum;
    cvBlob lowLargerBlob;
    
    
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
    
    //Debugging tools
    ofTrueTypeFont	verdana;
    
    //OSC config
    ofxOscSender sender;
    bool stateChanged;
    float timeStamp;
    string previousRoom;
    string currentRoom;
    
};
