#pragma once

#include "ofMain.h"
#include "spaceship.h"
#include "ProjectConstants.h"

enum class debris { Asteroid, Star, Planet };
class spaceObject
{
public:
	spaceObject();
	virtual ~spaceObject();

	ofVec2f m_position;
	ofImage m_image;
    debris type;

	virtual void setup();
	void update();
	void draw();
	ofVec2f getPos();
};

