#pragma once

#include "ofMain.h"
#include "spaceship.h"
#include "ProjectConstants.h"

class spaceObject
{
public:
	spaceObject();
	virtual ~spaceObject();

	ofVec2f m_position;
	ofImage m_image;
    string m_objID;

	virtual void setup();
	void update();
	void draw();
	ofVec2f getPos();
};

