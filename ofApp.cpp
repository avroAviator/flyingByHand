#include "ofApp.h"
#include "spaceObject.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0);

	//setting up the LeapMotion add-on
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);

	m_ship.load(ProjectConstants::IMG_PATH_SHIP);					//load our image
	m_start.load(ProjectConstants::IMG_PATH_START);

 

	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);		//cap framerate
	ofSetRectMode(OF_RECTMODE_CENTER);								//set rect to center for better control

    m_ship.resize(100.0f, 50.0f);
	m_ship.rotate90(-1);                                            //rotate ship for proper orientation (facing upwards) on startup

    m_score = 0;                                                    //starting score (default)

    m_font.loadFont(ProjectConstants::FONT_PATH_CONSOLAS, 30);

    //create our asteroids and stars using a factory
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
       
    //set default gamestart to the desired screen (start)
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

			cout << "ofPalmPos: " << ofToString(ofPalmPos) << endl;																				//output palm position in terminal: x, y, z
			cout << "ofPalmRot: " << ofToString(m_palmRot) << endl;
			cout << "pinchStrength: " << ofToString(m_pinchStrength) << endl;
			
            cout << "time visible: " << ofToString(m_screenTime) << endl;

			break;																																//only want one hand position so take the first detected as default
		}

        //updating objects drawn  (stars and asteroids)
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->update();
        }
        
        /*
        time visible
        when hand has been visible for every 5 seconds
        increment score+=1;
        */
        


	}
	else if (m_gameState == "end") {

	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (m_gameState == "start") {
        //draw start screen at center of window (can be dynamically done later)
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
			ofScale(m_pinchStrength + 1.3f, m_pinchStrength + 1.3f, m_pinchStrength + 1.3f);
			m_ship.draw(0.0f, 0.0f);
		ofPopMatrix();

       
        //drawing scoreboard
        ofPushMatrix();
            ofTranslate(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
            ofScale(1.0f, 1.0f);
            m_font.drawString("Score: " + ofToString(m_score), -630, 350);
        ofPopMatrix();
      
        
	}
	else if (m_gameState == "end") {

	}


}
