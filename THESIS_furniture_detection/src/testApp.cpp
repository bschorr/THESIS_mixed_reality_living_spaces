#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
	
    setKinect();
    setOpenCv();
	setGui();
    
    verdana.loadFont("verdana.ttf", 72, true, true);

}

//--------------------------------------------------------------
void testApp::update(){
    
    updateCv();
    
    if (
        lowBlobNum == 2 &&
        highBlobNum == 1 &&
        lowArea > 12000 &&
        highArea > 9000
        )
    {
        resetCurrentRoom();
        bDrawDining = true;
    } else if (
               lowBlobNum == 1 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               abs(lowLargerBlob.width - lowLargerBlob.height) < 100 &&
               lowLargerBlob.pos.x < 150
               )
    {
        resetCurrentRoom();
        bDrawOffice = true;
    } else if (
               lowBlobNum == 2 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               lowLargerBlob.pos.x < 150
               )
    {
        resetCurrentRoom();
        bDrawOffice = true;
    } else if (
               lowBlobNum == 1 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               abs(lowLargerBlob.width - lowLargerBlob.height) < 100 &&
               lowLargerBlob.pos.x > 300
               )
    {
        resetCurrentRoom();
        bDrawLibrary = true;
    } else if (
               lowBlobNum == 2 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               lowLargerBlob.pos.x > 300
               )
    {
        resetCurrentRoom();
        bDrawLibrary = true;
    } else if (
               lowBlobNum == 1 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               lowLargerBlob.width > lowLargerBlob.height
               )
    {
        resetCurrentRoom();
        bDrawBedroom = true;
    } else if (
               lowBlobNum == 1 &&
               highBlobNum == 0 &&
               lowArea > 17000 &&
               highArea < 1000 &&
               lowLargerBlob.width < lowLargerBlob.height
               )
    {
        resetCurrentRoom();
        bDrawCinema = true;
    }
    
    
    
    /*
    if (incomingPix.low > bedroomPix.low) {
        bDrawBedroom = true;
    } else if (incomingPix.low > cinemaPix.low && incomingPix.high > cinemaPix.high) {
        bDrawCinema = true;
    }
     */
    
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(100, 100, 100);
    
    if (bDrawDebug) drawDebug();
    
    string currentRoom;
    
    if (bDrawDining) {
        currentRoom = "Dining";
    } else if (bDrawOffice) {
        currentRoom = "Office";
    } else if (bDrawLibrary) {
        currentRoom = "Library";
    } else if (bDrawBedroom) {
        currentRoom = "Bedroom";
    } else if (bDrawCinema) {
        currentRoom = "Cinema";
    }
    
    verdana.drawString(currentRoom, 50, 350);
    
//    if (bDrawBedroom) cout << "drawing bedroom!" << endl;
//    if (bDrawCinema) cout << "drawing cinema!" << endl;

}

//--------------------------------------------------------------
void testApp::exit(){
    cvGui->saveSettings("cvGuiSettings.xml");
    //threshGui->saveSettings("threshGuiSettings.xml");
    delete cvGui;
    //delete threshGui;
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
void testApp::resetCurrentRoom() {
    bDrawBedroom = false;
    bDrawCinema = false;
    bDrawDining = false;
    bDrawLibrary = false;
    bDrawOffice = false;
}

//--------------------------------------------------------------
void testApp::setOpenCv() {
    
    colorImg.allocate(kinect.width, kinect.height);
	lowGrayThresh.allocate(kinect.width, kinect.height);
	highGrayThresh.allocate(kinect.width, kinect.height);
    
}

//--------------------------------------------------------------
void testApp::updateCv() {
    
    kinect.update();

    
    if(kinect.isFrameNew()) {
        
        kinectPixels.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        kinectPixels.crop(cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y);
        
        //lowGrayThresh.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        lowGrayThresh.setFromPixels(kinectPixels.getPixels(), kinectPixels.width, kinectPixels.height);
        highGrayThresh.setFromPixels(kinectPixels.getPixels(), kinectPixels.width, kinectPixels.height);
        
        //do the CV thresholding
        unsigned char * lowPix = lowGrayThresh.getPixels();
        unsigned char * highPix = highGrayThresh.getPixels();
        
        int lowNumPixels = lowGrayThresh.getWidth() * lowGrayThresh.getHeight();
        
        //acout << lowGrayThresh.getWidth() << endl;
        
        int highNumPixels = highGrayThresh.getWidth() * highGrayThresh.getHeight();
        
        for(int i = 0; i < lowNumPixels; i++) {
            if(lowPix[i] < lowNearThreshold && lowPix[i] > lowFarThreshold) {
                lowPix[i] = 255;
            } else {
                lowPix[i] = 0;
            }
        }
        
        for(int i = 0; i < highNumPixels; i++) {
            if(highPix[i] < highNearThreshold && highPix[i] > highFarThreshold) {
                highPix[i] = 255;
            } else {
                highPix[i] = 0;
            }
        }
        
        // update the cv images
        lowGrayThresh.setFromPixels(lowPix, cropSize.x, cropSize.y);
        highGrayThresh.setFromPixels(highPix, cropSize.x, cropSize.y);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        lowContourFinder.findContours(lowGrayThresh, blobMinSize, blobMaxSize, 5, false);
        
        highContourFinder.findContours(highGrayThresh, blobMinSize, blobMaxSize, 5, false);
        
    }
    
    lowArea = 0;
    highArea = 0;
    
    lowBlobNum = lowContourFinder.nBlobs;
    highBlobNum = highContourFinder.nBlobs;
    
    lowLargerBlob.reset();
    
    for (int i = 0; i < lowContourFinder.nBlobs; i++){
        
        lowArea += lowContourFinder.blobs[i].area;
        
        if (lowContourFinder.blobs[i].area > lowLargerBlob.area) {
            lowLargerBlob.index = i;
            lowLargerBlob.area = lowContourFinder.blobs[i].area;
            lowLargerBlob.width = lowContourFinder.blobs[i].boundingRect.getWidth();
            lowLargerBlob.height = lowContourFinder.blobs[i].boundingRect.getHeight();
            lowLargerBlob.pos = lowContourFinder.blobs[i].boundingRect.getCenter();
        }
    }
    
    for (int i = 0; i < highContourFinder.nBlobs; i++){
        highArea += highContourFinder.blobs[i].area;
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
    
    lowGrayThresh.draw(10, 320, kinectPixels.width, kinectPixels.height);
    lowContourFinder.draw(10, 320, kinectPixels.width, kinectPixels.height);
    
    highGrayThresh.draw(420, 320, kinectPixels.width, kinectPixels.height);
    highContourFinder.draw(420, 320, kinectPixels.width, kinectPixels.height);
    
    std::stringstream mainDebug;
    
    mainDebug <<
    "Framerate: " << ofGetFrameRate() << endl
    << "Low Blobs: " << lowBlobNum << endl
    << "Low Area: " << lowArea << endl
    << "High Blobs: " << highBlobNum << endl
    << "High Area: " << highArea << endl
    << "Low Larger Blob Width: " << lowLargerBlob.width << endl
    << "Low Larger Blob Height: " << lowLargerBlob.height;
    
    ofDrawBitmapString(mainDebug.str(), 30, 30);
    
    ofSetColor(255, 0, 0);
    
    for (int i = 0; i < lowContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(10, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << lowContourFinder.blobs[i].area << endl
        << "x: " << lowContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << lowContourFinder.blobs[i].boundingRect.getCenter().y << endl
        << "width: " << lowContourFinder.blobs[i].boundingRect.width << endl
        << "height: " << lowContourFinder.blobs[i].boundingRect.height;
        
        ofDrawBitmapString(output.str(), lowContourFinder.blobs[i].boundingRect.getCenter() + screenPos);
		}

    for (int i = 0; i < highContourFinder.nBlobs; i++){
        
        ofVec2f screenPos = ofVec2f(420, 320);
        
        std::stringstream output;
        
        output <<
        "area: " << highContourFinder.blobs[i].area << endl
        << "x: " << highContourFinder.blobs[i].boundingRect.getCenter().x << endl
        << "y: " << highContourFinder.blobs[i].boundingRect.getCenter().y << endl
        << "width: " << highContourFinder.blobs[i].boundingRect.width << endl
        << "height: " << highContourFinder.blobs[i].boundingRect.height;
        
        ofDrawBitmapString(output.str(), highContourFinder.blobs[i].boundingRect.getCenter()+screenPos);
    }
    
    ofSetColor(255);

    /*
    ofDrawBitmapString("IncomingPix - low: " + ofToString(incomingPix.low), 30, 50);
    ofDrawBitmapString("IncomingPix - high: " +ofToString(incomingPix.high), 30, 70);
    */
}

//--------------------------------------------------------------
void testApp::setGui() {
    
    cvGui = new ofxUISuperCanvas("CV");
    cvGui->addSpacer();
    cvGui->add2DPad("Crop Origin", ofPoint(0, 640), ofPoint(0, 480), cropOrigin);
    cvGui->add2DPad("Crop Size", ofPoint(0, 640), ofPoint(0, 480), cropOrigin);
    cvGui->addSlider("Low Near Threshold", 0, 255, lowNearThreshold);
    cvGui->addSlider("Low Far Threshold", 0, 255, lowFarThreshold);
    cvGui->addSlider("High Near Threshold", 0, 255, highNearThreshold);
    cvGui->addSlider("High Far Threshold", 0, 255, highFarThreshold);
    cvGui->addSlider("Angle", -30, 30, angle);
    cvGui->addSlider("Minimum Blob Size", 0, 30000, blobMinSize);
    cvGui->addSlider("Maximum Blob Size", 0, 30000, blobMaxSize);
    cvGui->addToggle("Draw Debug", bDrawDebug);
    cvGui->autoSizeToFitWidgets();
    ofAddListener(cvGui->newGUIEvent,this,&testApp::guiEvent);
    cvGui->loadSettings("cvGuiSettings.xml");
    //cvGui->setPosition(0, 0);
    
    /*
    threshGui = new ofxUISuperCanvas("Thresholds");
    threshGui->addSpacer();
    
    threshGui->addSlider("bedroomPix.low", 0, 100, bedroomPix.low);
    threshGui->addSlider("bedroomPix.high", 0, 100, bedroomPix.high);
    
    threshGui->addSlider("cinemaPix.low", 0, 100, cinemaPix.low);
    threshGui->addSlider("cinemaPix.high", 0, 100, cinemaPix.high);
    
    threshGui->autoSizeToFitWidgets();
    ofAddListener(threshGui->newGUIEvent,this,&testApp::guiEvent);
    threshGui->loadSettings("threshGuiSettings.xml");
    //threshGui->setPosition(212, 0);
     */
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
        
	} else if(name == "Low Near Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		lowNearThreshold = slider->getScaledValue();
	
    } else if(name == "Low Far Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		lowFarThreshold = slider->getScaledValue();
	
    } else if (name == "High Near Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		highNearThreshold = slider->getScaledValue();
        
    } else if(name == "High Far Threshold") {
        
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		highFarThreshold = slider->getScaledValue();
        
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
 /*
    //from here and under, it's Threshold Gui
    } else if (name == "bedroomPix.low") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bedroomPix.low = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "bedroomPix.high") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bedroomPix.high = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "cinemaPix.low") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        cinemaPix.low = slider->getNormalizedValue()*INPUTPIXELS;
        
    } else if (name == "cinemaPix.high") {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        cinemaPix.high = slider->getNormalizedValue()*INPUTPIXELS;
        cout << cinemaPix.high << endl;
        */
    }
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch (key) {
        case 'r':
            lowGrayThresh.resize(cropSize.x, cropSize.y);
            highGrayThresh.resize(cropSize.x, cropSize.y);
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


