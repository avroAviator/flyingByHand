#pragma once
#include "ofMain.h"
#include "ProjectConstants.h"

class spaceship
{
public:
    spaceship();
    ~spaceship();

     ofVec3f m_position;
	 float m_shipWidth = 50.0f;
	 float m_shipHeight = 100.0f;
     float m_collisionRad = (m_shipWidth);
     ofImage m_ship;

     void setPosition(int x, int z);
	 void setup();

};


