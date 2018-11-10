#include "ofApp.h"
#include "spaceObject.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//default background to black
	ofBackground(0);

	//setting up the LeapMotion add-on
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);

	//import starting screen image for instructions
	m_start.load(ProjectConstants::IMG_PATH_START);

	ofSetRectMode(OF_RECTMODE_CENTER);

	//setup ship class
	ship.setup();

	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);		//cap framerate

	m_prevFrame = false;

	m_score = 0;                                                    //starting score (default)

	//loading the font for drawing strings
	m_font.loadFont(ProjectConstants::FONT_PATH_CONSOLAS, 30);

	//create our asteroids and stars using a factory
	for (int i = 0; i < numAsteroids; i++) { objects.push_back(spaceFactory::m_createObject(objectTypes::Asteroid)); }
	for (int i = 0; i < numStars; i++) { objects.push_back(spaceFactory::m_createObject(objectTypes::Star)); }
	for (int i = 0; i < objects.size(); i++) { objects[i]->setup(); }

	//set default gamestart to the desired screen (start)
	m_gameState = "start";
}

//--------------------------------------------------------------
//get frame data everytime device is updated
void ofApp::onLeapFrame(Leap::Frame frame) {
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (m_gameState == "start") {
		//update device manually
		m_device.update();

		//store more than one hand for tracking
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

			//get value of grab and pinch strength (number between 0.0f and 1.0f)
			m_grabStrength = hand.grabStrength();

			//now change coordinates to middle of screen
			//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
			m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;																				//output palm position in terminal: x, y, z
			cout << "grabStrength: " << ofToString(m_grabStrength) << endl;

			if (m_grabStrength > 0.8f) {
				m_gameState = "game";
			}

			//only want one hand position so take the first detected as default
			break;
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

			//monitor screentime of tracked hand in seconds
			m_screenTime = hand.timeVisible();

			//scale values of the palm position to keep it on screen
			m_palmPos.x = ofPalmPos.x * 7.0f;
			m_palmPos.z = ofPalmPos.z * 5.0f;

			//now we need to set limits to screen so ship can't disappear
			m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f);
			m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			ship.m_position.x = m_palmPos.x;
			ship.m_position.z = m_palmPos.z;

			//get rotation from Leap data. Note that angles come in radians so we must convert.
			m_palmRot = ofVec3f(
				ofRadToDeg(hand.direction().pitch()),
				ofRadToDeg(hand.direction().yaw()),
				ofRadToDeg(hand.direction().roll())
			);

			//get value of grab and pinch strength (number between 0.0f and 1.0f)
			m_pinchStrength = hand.pinchStrength();

			//now change coordinates to middle of screen
			//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
			m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			cout << "time visible: " << ofToString(m_screenTime) << endl;

			break;																																//only want one hand position so take the first detected as default
		}

		//updating objects drawn  (stars and asteroids)
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->update();
			detectCollision(objects[i], ship, i);
		}

		//this is the score counter for time 'survived' on screen ( in secs )
		int totalTime = m_screenTime;

		if (totalTime % 5 == 0) {

			if (!m_prevFrame) {
				m_score++;
				m_prevFrame = true;
			}
		}
		else {
			m_prevFrame = false;
		}
	}
	else if (m_gameState == "end") {
		//update device manually
		m_device.update();

		//store more than one hand for tracking
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

			//get value of pinch strength (number between 0.0f and 1.0f)
			m_pinchStrength = hand.pinchStrength();

			//now change coordinates to middle of screen
			//note how up and down is the Y-axis on Leap and in and out of screen is z-axis!! ... transposing from a 3D space to a 2D screen
			m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

			cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;																				//output palm position in terminal: x, y, z
			cout << "pinchStrength: " << ofToString(m_pinchStrength) << endl;

			if (m_pinchStrength > 0.9f) { std::exit(0); }				//we want the game to close when user pinches

			//only want one hand position so take the first detected as default
			break;
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (m_gameState == "start") {
		//draw start screen at center of window
		ofPushMatrix();
		m_start.draw(640.0f, 360.0f);
		ofPopMatrix();
	}
	else if (m_gameState == "game") {

		ofPushMatrix();
			ofTranslate((ProjectConstants::PROJ_WINDOW_RES_X / 2), (ProjectConstants::PROJ_WINDOW_RES_Y / 2));
			for (int i = 0; i < objects.size(); i++) { objects[i]->draw(); }
		ofPopMatrix();

		//now draw ship moving relative to where we are detecting our hand
		ofPushMatrix();
			ofTranslate(m_palmPos.x, m_palmPos.z);
			ofRotateZ(m_palmRot.y);
			ofScale(m_pinchStrength + 1.3f, m_pinchStrength + 1.3f, m_pinchStrength + 1.3f);
			ship.m_ship.draw(0.0f, 0.0f);
		ofPopMatrix();

		//drawing scoreboard
		ofPushMatrix();
			ofTranslate(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
			ofScale(1.0f, 1.0f);
			m_font.drawString("Score: " + ofToString(m_score), -630, 350);
		ofPopMatrix();
	}
	else if (m_gameState == "end") {
		//drawing closing screen with final score
		ofPushMatrix();
			ofTranslate(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
			ofScale(1.0f, 1.0f);
			m_font.drawString("Game over!\nYour score was: " + ofToString(m_score) + "\nUse Pinch Gesture to exit game.", -300, 0);
		ofPopMatrix();
	}
}

void ofApp::detectCollision(spaceObject* obj, spaceship ship, int i) {

	if (sqrt(pow((obj->m_position.x - ship.m_position.x), 2) + pow((obj->m_position.y - ship.m_position.z), 2)) <= ship.m_collisionRad) {
		cout << "Collsion happened" << endl;

		if (obj->m_objID == "Star") {
			if (m_pinchStrength > 0.8f) {
				objects[i] = NULL;
				delete objects[i];
				objects.erase(objects.begin() + i);
				m_score++;
			}
		}
		else if (obj->m_objID == "Asteroid") {
			m_gameState = "end";
		}
	}
}