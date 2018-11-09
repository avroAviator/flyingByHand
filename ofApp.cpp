#include "ofApp.h"
#include "spaceObject.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	
	//setting up the LeapMotion add-on
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);

	m_ship.load(ProjectConstants::IMG_PATH_SHIP);					//load our image
	m_start.load("images/start.png");


	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);		//cap framerate
	ofSetRectMode(OF_RECTMODE_CENTER);								//set rect to center for better control

	m_ship.rotate90(3);

	for (int i = 0; i < numAsteroids; i++) {
		objects.push_back(spaceFactory::createObject(objectTypes::Asteroid));
	}
	for (int i = 0; i < numStars; i++) {
		objects.push_back(spaceFactory::createObject(objectTypes::Star));
	}

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setup();
	}

	initialDraw = true;
	numDrawn = 0;

	m_gameState = "start";
}

//--------------------------------------------------------------
//get frame data everytime device is updated
void ofApp::onLeapFrame(Leap::Frame frame){
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (m_gameState == "start") {
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


			//get rotation from Leap data. Note that angles come in radians so we must convert.
			m_palmRot = ofVec3f(
				ofRadToDeg(hand.direction().pitch()),
				ofRadToDeg(hand.direction().yaw()),
				ofRadToDeg(hand.direction().roll())
			);

			//get value of grab and pinch strength (number between 0.0f and 1.0f)
			m_grabStrength = hand.grabStrength();
			m_pinchStrength = hand.pinchStrength();

			//now change coordinates to middle of screen
			//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
			m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;																				//output palm position in terminal: x, y, z
			cout << "ofPalmRot: " << ofToString(m_palmRot) << endl;
			cout << "pinchStrength: " << ofToString(m_pinchStrength) << ", grabStrength: " << ofToString(m_grabStrength) << endl;


			break;																																//only want one hand position so take the first detected as default
		}
	}
	else if (m_gameState == "game") {
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


			//get rotation from Leap data. Note that angles come in radians so we must convert.
			m_palmRot = ofVec3f(
				ofRadToDeg(hand.direction().pitch()),
				ofRadToDeg(hand.direction().yaw()),
				ofRadToDeg(hand.direction().roll())
			);

			//get value of grab and pinch strength (number between 0.0f and 1.0f)
			m_grabStrength = hand.grabStrength();
			m_pinchStrength = hand.pinchStrength();

			//now change coordinates to middle of screen
			//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
			m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;																				//output palm position in terminal: x, y, z
			cout << "ofPalmRot: " << ofToString(m_palmRot) << endl;
			cout << "pinchStrength: " << ofToString(m_pinchStrength) << ", grabStrength: " << ofToString(m_grabStrength) << endl;
			
			for (int i = 0; i < objects.size(); i++) {
				objects[i]->update();
			}


			break;																																//only want one hand position so take the first detected as default
		}
	}
	else if (m_gameState == "end") {

	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (m_gameState == "start") {
		ofPushMatrix();
			m_start.draw(640.0f, 360.0f);
		ofPopMatrix();
	}
	else if (m_gameState == "game") {
		
		//if (numDrawn < objects.size()) {

		//}
		//else {
			for (int i = 0; i < objects.size(); i++) {
				objects[i]->draw();
			}
		//}
		
		//now draw ship moving relative to where we are detecting our hand
		ofPushMatrix();
			ofTranslate(m_palmPos.x, m_palmPos.z);
			ofRotateZ(m_palmRot.y);
			ofScale(m_pinchStrength + 0.5f, m_pinchStrength + 0.5f, m_pinchStrength + 0.5f);
			m_ship.draw(0.0f, 0.0f, 100.0f, 200.0f);
		ofPopMatrix();
	}
	else if (m_gameState == "end") {

	}


}
