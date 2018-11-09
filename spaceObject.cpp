#include "spaceObject.h"

spaceObject::spaceObject()
{
}
spaceObject::~spaceObject()
{
}

void spaceObject::setup(){
}

void spaceObject::update(){

	m_position.y = m_position.y++;

	if (m_position.y >= ofGetWindowHeight() + (m_image.getHeight() / 2)) {
		m_position.x = rand() % ofGetWindowWidth();
		m_position.y = 0;
	}
}

void spaceObject::draw(){
	m_image.draw(m_position.x, m_position.y);
}

ofVec2f spaceObject::getPos()
{
	return m_position;
}