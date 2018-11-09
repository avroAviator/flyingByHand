#pragma once

#include "ofMain.h"
#include "spaceObject.h"
#include "Asteroid.h"
#include "Star.h"
#include "spaceFactory.h"

#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		std::vector<spaceObject*> objects;
		bool initialDraw;
		int numDrawn;
		int numAsteroids = 15;
		int numStars = 10;

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
		
};
