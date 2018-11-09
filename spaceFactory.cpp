#include "spaceFactory.h"
#include "spaceObject.h"
#include "Asteroid.h"
//#include "Planet.h"
#include "Star.h"

spaceFactory* spaceFactory::m_spaceFactory = 0;

spaceFactory::spaceFactory() {}

spaceObject* spaceFactory::createObject(objectTypes type)
{
	switch (type)
	{
	case objectTypes::Asteroid:
		return new Asteroid();
		break;
	case objectTypes::Star:
		return new Star();
		break;
	//case objectTypes::Planet:
	//	return new Planet();
	//	break;
	default:
		break;
	}
}