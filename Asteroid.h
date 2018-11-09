#pragma once
#include "spaceObject.h"

class Asteroid : public spaceObject{

public:
	Asteroid();
	~Asteroid();

	void setup();
    objectTypes spaceObject::type = objectTypes::Asteroid;

};

