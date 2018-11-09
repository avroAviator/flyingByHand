#include "Asteroid.h"

Asteroid::Asteroid(){
}

Asteroid::~Asteroid(){
}

void Asteroid::setup() {

	m_image.load("Asteroid.png");
	m_image.resize(30,60);
	m_image.setAnchorPoint(m_image.getWidth(), m_image.getHeight());

	m_position.x = rand () % ofGetWindowWidth();
	m_position.y = rand () % ofGetWindowHeight();
}