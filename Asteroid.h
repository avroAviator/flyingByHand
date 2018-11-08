#pragma once
#include "spaceObject.h"

class Asteroid : public spaceObject
{
public:
	Asteroid() {}

	void setup() {

		m_position.x = rand() % ofGetWindowWidth();
		m_position.y = 0;

		m_image.load("Asteroid.png");
	}

};