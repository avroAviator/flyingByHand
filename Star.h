#pragma once
#include "spaceObject.h"


class Star :public spaceObject
{
public:
	Star();
	~Star();

	void setup();
    objectTypes spaceObject::type = objectTypes::Star;
};

