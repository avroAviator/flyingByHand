#pragma once
#include "spaceFactory.h"
#include <cstdlib>

class spaceObject
{
public:
	ofVec2f m_position;
	ofImage m_image;

	ofVec2f getPosition();
	virtual void setup() = 0;
	void update();
	void draw();

};