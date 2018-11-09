#pragma once
#include "spaceObject.h"
#include "ofMain.h"

enum class objectTypes { Asteroid, Star, Planet };

class spaceFactory
{
public:

	static spaceObject* createObject(objectTypes type);

private:
	spaceFactory();
	static spaceFactory* m_spaceFactory;

};