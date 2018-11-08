#pragma once
#include "spaceObject.h"

class Star : public spaceObject
{
public:
	Star() {}

	ofVec2f getPosition() { return position; }

};