#include "spaceFactory.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Star.h"

spaceFactory* spaceFactory::m_spaceFactory = 0;

spaceFactory* spaceFactory::GetInstance()
{
	if (m_spaceFactory == 0)
		m_spaceFactory = new spaceFactory();
	return m_spaceFactory;
}

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
	case objectTypes::Planet:
		return new Planet();
		break;
	default:
		break;
	}
}