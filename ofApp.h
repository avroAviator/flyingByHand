#pragma once

#include "ofMain.h"
#include "ofxLeapC.h"

#include "ProjectConstants.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void onLeapFrame(Leap::Frame frame);

		ofxLeapC::Device	m_device;
		Leap::Frame			m_frame;
		

		//we are going to now track our palm position through a member varible we can use again in the draw function
		ofVec3f					m_palmPos;
		ofImage					m_ship;			//an image to represent our ship
};
