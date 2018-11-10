#include "spaceship.h"

spaceship::spaceship()
{
}


spaceship::~spaceship()
{
}

void spaceship::setPosition(int x, int z)
{
    m_position.x = x;
    m_position.z = z;
}

void spaceship::setup() {
	m_ship.load(ProjectConstants::IMG_PATH_SHIP);
	m_ship.resize(100.0f, 50.0f);
	m_ship.rotate90(-1);

	m_ship.setAnchorPoint(m_shipWidth / 2.0f, m_shipHeight / 2.0f);
}
