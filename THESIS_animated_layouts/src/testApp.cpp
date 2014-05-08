#include "testApp.h"
#include "Bedroom.h"
#include "Office.h"
#include "Dining.h"
#include "Library.h"
#include "Cinema.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(true);
    ofSetBackgroundAuto(false);
    //ofEnableAlphaBlending();
    //ofEnableSmoothing();
    
    //setup shared data
	stateMachine.getSharedData().wallComplete.allocate(1870, 800, GL_RGBA);
    stateMachine.getSharedData().syphonOut.allocate(1870, 800, GL_RGBA);
    stateMachine.getSharedData().wallOne.allocate(935, 800, GL_RGBA);
    stateMachine.getSharedData().wallTwo.allocate(935, 800, GL_RGBA);
	stateMachine.getSharedData().isTransition = false;
    
    stateMachine.getSharedData().syphonOut.begin();
        ofClear(255,255,255, 0);
    stateMachine.getSharedData().syphonOut.end();
    
	// initialise state machine
	stateMachine.addState<Bedroom>();
	stateMachine.addState<Office>();
    stateMachine.addState<Dining>();
    stateMachine.addState<Library>();
    stateMachine.addState<Cinema>();
	stateMachine.changeState("office");
    
    //setup OSC receiver
    receiver.setup(PORT);
    
    //setup syphon
    syphonOutput.setName("Texture Output");
    
    //mask shaders
    stateMachine.getSharedData().maskShader.load("shaders/composite");
    
    //pos utils
    stateMachine.getSharedData().xPos = 0;
    stateMachine.getSharedData().yPos = 0;
    
    //transitions
    transition.setup( &stateMachine );

}

//--------------------------------------------------------------
void testApp::update(){
    
    stateMachine.getSharedData().wallComplete.begin();
        ofClear(0, 0, 0);
        stateMachine.getSharedData().wallOne.draw(0, 0);
        stateMachine.getSharedData().wallTwo.draw(935, 0);
    stateMachine.getSharedData().wallComplete.end();
    
    if (stateMachine.getSharedData().isTransition) {
        transition.update();
        stateMachine.getSharedData().syphonOut.begin();
        ofEnableAlphaBlending();
        stateMachine.getSharedData().maskFrames(stateMachine.getSharedData().wallComplete, transition.fbo);
        ofDisableAlphaBlending();
        stateMachine.getSharedData().syphonOut.end();
    } else {
        stateMachine.getSharedData().syphonOut.begin();
        stateMachine.getSharedData().wallComplete.draw(0, 0);
        stateMachine.getSharedData().syphonOut.end();
    }
    
    //process OSC messages
    oscReceive();
    
    //reset color to white
    ofClear (0, 0);
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofDisableAlphaBlending();
    stateMachine.getSharedData().syphonOut.draw(0, 0);

    ofDrawBitmapString(ofToString(ofGetFrameRate()), 30, 50);
    
    ofDrawBitmapString(ofToString("xPos: " + ofToString(stateMachine.getSharedData().xPos) + " / yPos: " + ofToString(stateMachine.getSharedData().yPos)), 30, 70);
    
    ofTexture tex = stateMachine.getSharedData().syphonOut.getTextureReference();
    syphonOutput.publishTexture( &tex );
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::oscReceive(){
    
    while(receiver.hasWaitingMessages()){
        
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/room"){
            
            string msgString;
            msgString = m.getArgAsString(0);
            cout << msgString << endl;
            
            if (msgString == "bedroom") {
                stateMachine.changeState("bedroom");
            } else if (msgString == "office") {
                stateMachine.changeState("office");
            } else if (msgString == "dining") {
                stateMachine.changeState("dining");
            } else if (msgString == "library") {
                stateMachine.changeState("library");
            } else if (msgString == "cinema") {
                stateMachine.changeState("cinema");
            }
            
            
        }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
            stateMachine.getSharedData().yPos -= stateMachine.getSharedData().inc;
            break;
        case OF_KEY_DOWN:
            stateMachine.getSharedData().yPos+= stateMachine.getSharedData().inc;
            break;
        case OF_KEY_RIGHT:
            stateMachine.getSharedData().xPos+=stateMachine.getSharedData().inc;
            break;
        case OF_KEY_LEFT:
            stateMachine.getSharedData().xPos-=stateMachine.getSharedData().inc;
            break;
        case '1':
            stateMachine.getSharedData().inc = 1;
            break;
        case '2':
            stateMachine.getSharedData().inc = 10;
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
