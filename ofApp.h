#pragma once

//May want to look here: https://developer.leapmotion.com/documentation/v4/group___structs.html#struct_l_e_a_p___h_a_n_d 

#include "ofMain.h"
#include "ofxLeapC.h"

#include "ProjectConstants.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void onLeapFrame(Leap::Frame frame);

		ofxLeapC::Device		m_device;
		Leap::Frame				m_frame;

		ofVec3f					m_palmPos;
		ofVec3f					m_palmRot;
		float					m_pinchStrength;
		float					m_grabStrength;
		ofImage					m_ship;

		ofFloatColor			m_bgCol;
};
