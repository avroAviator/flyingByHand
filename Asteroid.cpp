#include "Asteroid.h"

Asteroid::Asteroid(){
}

Asteroid::~Asteroid(){
}

void Asteroid::setup() {

	m_image.load(ProjectConstants::IMG_PATH_ASTEROID);
	m_image.resize(30,60);
	m_image.setAnchorPoint(m_image.getWidth(), m_image.getHeight());

	m_position.x = rand() % (ofGetWindowWidth() / 2) + (-ofGetWindowWidth() / 2);
	m_position.y = rand() % (ofGetWindowHeight() / 2) + (-ofGetWindowHeight() / 2);

	m_objID = "Asteroid";
}