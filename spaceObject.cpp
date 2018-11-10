#include "spaceObject.h"

spaceObject::spaceObject()
{
}
spaceObject::~spaceObject()
{
}

void spaceObject::setup() {
}

void spaceObject::update() {

	m_position.y = m_position.y++;

	if (m_position.y >= (ofGetWindowHeight() / 2) + (m_image.getHeight())) {
		m_position.x = rand() % (ofGetWindowWidth() + 1) + (-ofGetWindowWidth() / 2);
		m_position.y = -360;
	}
}

void spaceObject::draw() {
	m_image.draw(m_position.x, m_position.y);
}

ofVec2f spaceObject::m_getPos()
{
	return m_position;
}
