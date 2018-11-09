#pragma once
#include "ofMain.h"

class spaceship
{
public:
    spaceship();
    ~spaceship();

     ofVec3f m_position;
     float collisionRad = 20.0f;
     float shipWidth = 100.0f;
     float shipHeight = 200.0f;

     void setPosition(int x, int z);

};

