#pragma once

#include "ofMain.h"
#include "ofxLeapC.h"

#include "spaceObject.h"
#include "Asteroid.h"
#include "Star.h"
#include "spaceFactory.h"
#include <vector>

#include "ProjectConstants.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void onLeapFrame(Leap::Frame frame);
		void detectCollision(spaceObject* obj, spaceship ship, int i);

		ofxLeapC::Device	m_device;
		Leap::Frame			m_frame;
		

		//we are going to now track our palm position through a member varible we can use again in the draw function
		ofVec3f					m_palmPos;
		ofVec3f					m_palmRot;
		ofImage					m_start;		//an image to represent the 'start' screen


		spaceship ship;
		float m_pinchStrength;
		float m_grabStrength;
		
		string m_gameState;
		int m_score;

        float m_screenTime;

        ofTrueTypeFont m_font;
	
		std::vector<spaceObject*> objects;
		bool initialDraw;
		int numDrawn;
		int numAsteroids = 15;
		int numStars = 10;

};
