#pragma once

#include "ofMain.h"
#include "ofxLeapC.h"

#include "ProjectConstants.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void onLeapFrame(Leap::Frame frame);

		ofxLeapC::Device	m_device;
		Leap::Frame			m_frame;
		

		//we are going to now track our palm position through a member varible we can use again in the draw function
		ofVec3f					m_palmPos;
		ofVec3f					m_palmRot;
		ofImage					m_ship;			//an image to represent our ship
		ofImage					m_start;		//an image to represent the 'start' screen


		float m_pinchStrength;
		float m_grabStrength;
		
		string m_gameState;
		float m_score;

};
