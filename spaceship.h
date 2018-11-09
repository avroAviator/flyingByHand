#pragma once
#include "ofMain.h"
#include "ProjectConstants.h"

class spaceship
{
public:
    spaceship();
    ~spaceship();

     ofVec3f m_position;
     float collisionRad = 20.0f;
     float shipWidth = 100.0f;
     float shipHeight = 200.0f;
     ofImage m_ship;

     void setPosition(int x, int z);
     void setup() { m_ship.load(ProjectConstants::IMG_PATH_SHIP);
     m_ship.resize(100.0f, 50.0f);
     m_ship.rotate90(-1);}

};


