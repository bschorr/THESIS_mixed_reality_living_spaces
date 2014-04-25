#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(40, 100, 40);
    
    room = "no room selected!";

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    std::stringstream drawInfo;
    
    drawInfo << "now drawing: " << room << endl << endl <<
    "Press '1' to draw bedroom" << endl <<
    "Press '2' to draw office" << endl <<
    "Press '3' to draw dining" << endl <<
    "Press '4' to draw library" << endl <<
    "Press '5' to draw cinema" << endl;
    
	ofDrawBitmapString(drawInfo.str(), 30, 30);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
    switch (key) {
        case '1':
            room = "bedroom";
            break;
        
        case '2':
            room = "office";
            break;
        
        case '3':
            room = "dining";
            break;
            
        case '4':
            room = "library";
            break;
            
        case '5':
            room = "cinema";
            break;
            
        default:
            room = "no room selected!";
            break;
    }
        
        ofxOscMessage m;
        m.setAddress("/room");
        m.addStringArg(room);
        sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
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

