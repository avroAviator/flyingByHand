#pragma once
#include "spaceObject.h"


class Star :public spaceObject
{
public:
	Star();
	~Star();

	void setup();
    debris type = debris::Star;
};

