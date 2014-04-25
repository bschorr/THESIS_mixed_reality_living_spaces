#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxStateMachine.h"
#include "SharedData.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{

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
    
    
        //to receive incoming messages
        void oscReceive ();
        ofxOscReceiver receiver;
    
    private:
    //to control states
        itg::ofxStateMachine<SharedData> stateMachine;
    
};