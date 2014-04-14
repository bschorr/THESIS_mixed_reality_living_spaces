#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
	
    setKinect();
    setOpenCv();
	setGui();

}

//--------------------------------------------------------------
void testApp::update(){
    
    updateCv();
    
    bDrawBedroom = false;
    bDrawCinema = false;
    bDrawDining = false;
    bDrawLibrary = false;
    bDrawOffice = false;
    
    
    
    /*
    if (incomingPix.first > bedroomPix.first) {
        bDrawBedroom = true;
    } else if (incomingPix.first > cinemaPix.first && incomingPix.second > cinemaPix.second) {
        bDrawCinema = true;
    }
     */
    
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(100, 100, 100);
    
    if (bDrawDebug) drawDebug();
    
//    if (bDrawBedroom) cout << "drawing bedroom!" << endl;
//    if (bDrawCinema) cout << "drawing cinema!" << endl;

}

//--------------------------------------------------------------
void testApp::exit(){
    cvGui->saveSettings("cvGuiSettings.xml");
    threshGui->saveSettings("threshGuiSettings.xml");
    delete cvGui;
    delete threshGui;
}

//--------------------------------------------------------------
void testApp::setKinect() {
    // enable depth->video image calibration
	kinect.setRegistration(true);
    
    //init with video image for debugging
    kinect.init();
    
    // init disabling video image (faster fps)
	//kinect.init(false, false);
    
    // make sure everything is working
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
    
    // zero the tilt on startup (does this really work?)
	angle = 0;
	kinect.setCameraTiltAngle(angle);
}

//--------------------------------------------------------------
void testApp::setOpenCv() {
    
    colorImg.allocate(kinect.width, kinect.height);
	firstGrayThresh.allocate(kinect.width, kinect.height);
	secondGrayThresh.allocate(kinect.width, kinect.height);
    
}

//--------------------------------------------------------------
void testApp::updateCv() {
    
    kinect.update();

    
    if(kinect.isFrameNew()) {
        
        kinectPixels.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        kinectPixels.crop(cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y);
        
        //firstGrayThresh.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        firstGrayThresh.setFromPixels(kinectPixels.getPixels(), kinectPixels.width, kinectPixels.height);
        secondGrayThresh.setFromPixels(kinectPixels.getPixels(), kinectPixels.width, kinectPixels.height);
        
        incomingPix.first = 0;
        incomingPix.second = 0;
        
        //do the CV thresholding
        unsigned char * firstPix = firstGrayThresh.getPixels();
        unsigned char * secondPix = secondGrayThresh.getPixels();
        
        int firstNumPixels = firstGrayThresh.getWidth() * firstGrayThresh.getHeight();
        
        //acout << firstGrayThresh.getWidth() << endl;
        
        int secondNumPixels = secondGrayThresh.getWidth() * secondGrayThresh.getHeight();
        
        for(int i = 0; i < firstNumPixels; i++) {
            if(firstPix[i] < firstNearThreshold && firstPix[i] > firstFarThreshold) {
                firstPix[i] = 255;
                incomingPix.first++;
            } else {
                firstPix[i] = 0;
            }
        }
        
        for(int i = 0; i < secondNumPixels; i++) {
            if(secondPix[i] < secondNearThreshold && secondPix[i] > secondFarThreshold) {
                secondPix[i] = 255;
                incomingPix.second++;
            } else {
                secondPix[i] = 0;
            }
        }
        
        // update the cv images
        firstGrayThresh.setFromPixels(firstPix, cropSize.x, cropSize.y);
        secondGrayThresh.setFromPixels(secondPix, cropSize.x, cropSize.y);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        firstContourFinder.findContours(firstGrayThresh, blobMinSize, blobMaxSize, 5, false);
        
        secondContourFinder.findContours(secondGrayThresh, blobMinSize, blobMaxSize, 5, false);
        
    }
    
    lowArea = 0;
    highArea = 0;
    
    lowBlobNum = 0;
    highBlobNum = 0;
    
    for (int i = 0; i < firstContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(10, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << firstContourFinder.blobs[i].area << endl
        << "x: " << firstContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << firstContourFinder.blobs[i].boundingRect.getCenter().y;
        
        ofDrawBitmapString(output.str(), firstContourFinder.blobs[i].boundingRect.getCenter() + screenPos);
    }
    
    for (int i = 0; i < secondContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(420, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << secondContourFinder.blobs[i].area << endl
        << "x: " << secondContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << secondContourFinder.blobs[i].boundingRect.getCenter().y;
        
        ofDrawBitmapString(output.str(), secondContourFinder.blobs[i].boundingRect.getCenter()+screenPos);
    }
    
    ofSetColor(255);
    
}

//--------------------------------------------------------------
void testApp::drawDebug(){
    
    kinect.drawDepth(10, 10, 400, 300);
    
    kinect.draw(420, 10, 400, 300);
    
    //draw the red rectangles for area debugging
    ofNoFill();
    
    ofSetColor(255, 0, 0);
    
    ofRect(10+(cropOrigin.x/1.6), 10+(cropOrigin.y/1.6), cropSize.x/1.6, cropSize.y/1.6);
    
    ofRect(420+(cropOrigin.x/1.6), 10+(cropOrigin.y/1.6), cropSize.x/1.6, cropSize.y/1.6);
    
    ofSetColor(255);
    
    firstGrayThresh.draw(10, 320, kinectPixels.width, kinectPixels.height);
    firstContourFinder.draw(10, 320, kinectPixels.width, kinectPixels.height);
    
    secondGrayThresh.draw(420, 320, kinectPixels.width, kinectPixels.height);
    secondContourFinder.draw(420, 320, kinectPixels.width, kinectPixels.height);
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 30, 30);
    
    ofSetColor(255, 0, 0);
    
    for (int i = 0; i < firstContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(10, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << firstContourFinder.blobs[i].area << endl
        << "x: " << firstContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << firstContourFinder.blobs[i].boundingRect.getCenter().y;
        
        ofDrawBitmapString(output.str(), firstContourFinder.blobs[i].boundingRect.getCenter() + screenPos);
		}

    for (int i = 0; i < secondContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(420, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << secondContourFinder.blobs[i].area << endl
        << "x: " << secondContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << secondContourFinder.blobs[i].boundingRect.getCenter().y;
        
        ofDrawBitmapString(output.str(), secondContourFinder.blobs[i].boundingRect.getCenter()+screenPos);
    }
    
    ofSetColor(255);

    /*
    ofDrawBitmapString("IncomingPix - First: " + ofToString(incomingPix.first), 30, 50);
    ofDrawBitmapString("IncomingPix - Second: " +ofToString(incomingPix.second), 30, 70);
    */
}

//--------------------------------------------------------------
void testApp::setGui() {
    
    cvGui = new ofxUISuperCanvas("CV");
    cvGui->addSpacer();
    cvGui->add2DPad("Crop Origin", ofPoint(0, 640), ofPoint(0, 480), cropOrigin);
    cvGui->add2DPad("Crop Size", ofPoint(0, 640), ofPoint(0, 480), cropOrigin);
    cvGui->addSlider("First Near Threshold", 0, 255, firstNearThreshold);
    cvGui->addSlider("First Far Threshold", 0, 255, firstFarThreshold);
    cvGui->addSlider("Second Near Threshold", 0, 255, secondNearThreshold);
    cvGui->addSlider("Second Far Threshold", 0, 255, secondFarThreshold);
    cvGui->addSlider("Angle", -30, 30, angle);
    cvGui->addSlider("Minimum Blob Size", 0, 20000, blobMinSize);
    cvGui->addSlider("Maximum Blob Size", 0, 20000, blobMaxSize);
    cvGui->addToggle("Draw Debug", bDrawDebug);
    cvGui->autoSizeToFitWidgets();
    ofAddListener(cvGui->newGUIEvent,this,&testApp::guiEvent);
    cvGui->loadSettings("cvGuiSettings.xml");
    //cvGui->setPosition(0, 0);
    
    threshGui = new ofxUISuperCanvas("Thresholds");
    threshGui->addSpacer();
    
    threshGui->addSlider("bedroomPix.first", 0, 100, bedroomPix.first);
    threshGui->addSlider("bedroomPix.second", 0, 100, bedroomPix.second);
    
    threshGui->addSlider("cinemaPix.first", 0, 100, cinemaPix.first);
    threshGui->addSlider("cinemaPix.second", 0, 100, cinemaPix.second);
    
    threshGui->autoSizeToFitWidgets();
    ofAddListener(threshGui->newGUIEvent,this,&testApp::guiEvent);
    threshGui->loadSettings("threshGuiSettings.xml");
    //threshGui->setPosition(212, 0);
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	
    if(name == "Crop Origin")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget;
		cropOrigin.x = pad->getPercentValue().x*640;
		cropOrigin.y = pad->getPercentValue().y*480;
	}
    
    else if(name == "Crop Size")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget;
		cropSize.x = pad->getPercentValue().x*640;
		cropSize.y = pad->getPercentValue().y*480;
        
	} else if(name == "First Near Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		firstNearThreshold = slider->getScaledValue();
	
    } else if(name == "First Far Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		firstFarThreshold = slider->getScaledValue();
	
    } else if (name == "Second Near Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		secondNearThreshold = slider->getScaledValue();
        
    } else if(name == "Second Far Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		secondFarThreshold = slider->getScaledValue();
        
    } else if (name == "Angle") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
		angle = slider->getScaledValue();
        kinect.setCameraTiltAngle(angle);
    
    } else if (name == "Minimum Blob Size") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
		blobMinSize = slider->getScaledValue();
        
    } else if (name == "Maximum Blob Size") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
		blobMaxSize = slider->getScaledValue();
        
    } else if (name == "Draw Debug") {
        
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		bDrawDebug = toggle->getValue();
        
    //from here and under, it's Threshold Gui
    } else if (name == "bedroomPix.first") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bedroomPix.first = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "bedroomPix.second") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bedroomPix.second = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "cinemaPix.first") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        cinemaPix.first = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "cinemaPix.second") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        cinemaPix.second = slider->getNormalizedValue()*INPUTPIXELS;
        cout << cinemaPix.second << endl;
        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch (key) {
        case 'r':
            firstGrayThresh.resize(cropSize.x, cropSize.y);
            secondGrayThresh.resize(cropSize.x, cropSize.y);
            break;
            
        default:
            break;
    }

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


