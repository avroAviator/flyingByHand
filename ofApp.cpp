#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);

	m_ship.load(ProjectConstants::IMG_PATH_SHIP);
	
	m_bgCol = ofFloatColor::white;		//make sure to initialize

	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);
}

void ofApp::onLeapFrame(Leap::Frame frame)
{
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_device.update();

	const Leap::HandList& hands = m_frame.hands();

	//	ofLogNotice( "OF_APP", "hand count: " + ofToString( hands.count() ) ); 

	for (int i = 0; i < hands.count(); ++i)
	{
		const Leap::Hand& hand = hands[i];
		const Leap::Vector palmPos			= hand.palmPosition();
		const ofVec3f ofPalmPos				= ofxLeapC::toVec3(hand.palmPosition());
		const ofVec3f ofStablizedPalmPos	= ofxLeapC::toVec3(hand.stabilizedPalmPosition());

		//get value of grab and pinch strength (number between 0.0f and 1.0f)
		m_grabStrength	= hand.grabStrength();
		m_pinchStrength = hand.pinchStrength();

		//get rotation from Leap data. Note that angles come in radians so we must convert
		m_palmRot = ofVec3f(
												ofRadToDeg( hand.direction().pitch() ),
												ofRadToDeg( hand.direction().yaw() ),
												ofRadToDeg( hand.direction().roll() )
											);

		//ofLogNotice("OF_APP", "ofPalmPos: "				+ ofToString(ofPalmPos));
		//ofLogNotice("OF_APP", "ofStablizedPalmPos: "	+ ofToString(ofStablizedPalmPos));
		//ofLogNotice("OF_APP", "ofPalmRot: " + ofToString(m_palmRot));

		cout << "pinchStrength: " << ofToString(m_pinchStrength) << ", grabStrength: " << ofToString(m_grabStrength) << endl;

		//need to scale values. We do not use mapping as depending on the height of the hand teh boundaries change ( a frustum/come shape is visible to sensor so the lower the hand the less space to move in
		m_palmPos.x = ofPalmPos.x * 7.0f;
		m_palmPos.z = ofPalmPos.z * 5.0f;

		//now we need to set limits to screen so ship can't disappear
		m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f );
		m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		//now change coordinates to middle of screen
		//note how up and down is the Y-axis on Leap and in and out of screen is z-axis ... transposing from a 3D space to a 2D screen
		m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		break; //only want one hand position so take the first detected as default ... perhaps a bit hacky. What is a better way?
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(ofFloatColor(m_grabStrength, 0.0f, 0.0f, 1.0f));

	ofSetRectMode(OF_RECTMODE_CENTER);

	ofPushMatrix();
		ofTranslate(m_palmPos.x, m_palmPos.z);
		//ofRotateY(m_palmRot.z);
		ofRotateZ(m_palmRot.y);
		ofScale(m_pinchStrength + 0.5f, m_pinchStrength + 0.5f, m_pinchStrength + 0.5f);
		m_ship.draw(0.0f, 0.0f);
	ofPopMatrix();
}
