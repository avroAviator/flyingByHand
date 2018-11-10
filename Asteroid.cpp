#include "Asteroid.h"

Asteroid::Asteroid() {
}

Asteroid::~Asteroid() {
}

void Asteroid::setup() {

	m_image.load(ProjectConstants::IMG_PATH_ASTEROID);
	m_image.resize(30, 60);
	m_image.setAnchorPoint(m_image.getWidth(), m_image.getHeight());

	m_position.x = rand() % ((ProjectConstants::PROJ_WINDOW_RES_X) + 1) + (-(ProjectConstants::PROJ_WINDOW_RES_X) / 2);
	m_position.y = rand() % (ofGetWindowHeight() + 1) + (-ofGetWindowHeight() / 2);

	m_objID = "Asteroid";
}