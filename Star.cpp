#include "Star.h"

Star::Star()
{
}


Star::~Star()
{
}

void Star::setup() {
	m_image.load(ProjectConstants::IMG_PATH_STAR);
	m_image.resize(70, 70);
	m_image.setAnchorPoint(m_image.getWidth(), m_image.getHeight());

	m_position.x = rand() % (ofGetWindowWidth() + 1) + (-ofGetWindowWidth() / 2);
	m_position.y = rand() % (ofGetWindowHeight() + 1) + (-ofGetWindowHeight() / 2);

	m_objID = "Star";
}
