#include "testApp.h"
#include "Bedroom.h"
#include "Office.h"
#include "Dining.h"
#include "Library.h"
#include "Cinema.h"

//--------------------------------------------------------------
void testApp::setup(){

    //setup shared data
	stateMachine.getSharedData().counter = 0;
	stateMachine.getSharedData().lastUpdate = 0;
	
	// initialise state machine
	stateMachine.addState<Bedroom>();
	stateMachine.addState<Office>();
    stateMachine.addState<Dining>();
    stateMachine.addState<Library>();
    stateMachine.addState<Cinema>();
	stateMachine.changeState("bedroom");
    
    //setup OSC receiver
    receiver.setup(PORT);

}

//--------------------------------------------------------------
void testApp::update(){
    
    //process OSC messages
    oscReceive();
    
}

//--------------------------------------------------------------
void testApp::draw(){

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
