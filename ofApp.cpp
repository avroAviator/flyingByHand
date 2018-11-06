#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//setting up the LeapMotion add-on
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);

	m_ship.load(ProjectConstants::IMG_PATH_SHIP);					//load our image

	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);		//cap framerate
	ofSetRectMode(OF_RECTMODE_CENTER);								//set rect to center for better control


}

//--------------------------------------------------------------
//get frame data everytime device is updated
void ofApp::onLeapFrame(Leap::Frame frame){
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update(){
	//update device manually
	m_device.update();
	

	//store more than one hand for tracking (though our program will probably only use one hand)
	const Leap::HandList& hands = m_frame.hands();




	//loop thru hands to obtain position. If another hand is detected, it can now be differentiated
	for (int i = 0; i < hands.count(); ++i)
	{
		const Leap::Hand& hand = hands[i];
		const Leap::Vector palmPos = hand.palmPosition();							//get the Leap palm position
		const ofVec3f ofPalmPos = ofxLeapC::toVec3(hand.palmPosition());			//convert palmPos LeapVec to a ofVec3f we can more easily work with


		//scale values of the palm position to keep it on screen
		m_palmPos.x = ofPalmPos.x * 7.0f;
		m_palmPos.z = ofPalmPos.z * 5.0f;


		//now we need to set limits to screen so ship can't disappear
		m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f);
		m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		//now change coordinates to middle of screen
		//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
		m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;						//output palm position in terminal: x, y, z

		break;																		//only want one hand position so take the first detected as default
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//now draw ship moving relative to where we are detecting our hand
	ofPushMatrix();
		ofTranslate(m_palmPos.x, m_palmPos.z);
		m_ship.draw(0.0f, 0.0f);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
