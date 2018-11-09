#pragma once

#include "ofMain.h"
#include "spaceship.h"
#include "spaceFactory.h"
#include "ProjectConstants.h"


class spaceObject
{
public:
	spaceObject();
	virtual ~spaceObject();

	ofVec2f m_position;
	ofImage m_image;
    objectTypes type;

	virtual void setup();
	void update();
	void draw();
	ofVec2f getPos();
};

