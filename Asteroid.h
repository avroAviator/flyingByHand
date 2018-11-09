#pragma once
#include "spaceObject.h"

class Asteroid : public spaceObject{

public:
	Asteroid();
	~Asteroid();

	void setup();
    debris type = debris::Asteroid;

};

