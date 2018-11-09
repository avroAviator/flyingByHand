#pragma once

#include "ofMain.h"

class spaceObject
{
public:
	spaceObject();
	virtual ~spaceObject();

	ofVec2f m_position;
	ofImage m_image;

	virtual void setup();
	void update();
	void draw();
	ofVec2f getPos();

};

