#pragma once

//This is a style of programming that I enjoy. Having all constants in one place so I can change anything in the project easily, 
//and in one place (without having to write twice .h and .cpp) as they global and not containing to any one class.

//As James mentioned we all have different coding styles so experiment and determine w=hat works best for you. For today we will use this style to show you
//some other ways to roagnize your code using consts and namespaces (not a class - just a way to organize similarly named variables and functions without conflict within a project).

#include "ofMain.h"

namespace ProjectConstants
{
	//app consts
	static const int		PROJ_WINDOW_RES_X = 1280;
	static const int		PROJ_WINDOW_RES_Y = 720;
	static const float		PROJ_DESIRED_FRAMERATE = 60.0f;

	//asset consts
	static const string		IMG_PATH_SHIP = "images/spaceship.png";
    static const string     IMG_PATH_START = "images/start.png";
    static const string     IMG_PATH_STAR = "images/Star.png";
    static const string     IMG_PATH_ASTEROID = "images/asteroid.png";
    static const string     FONT_PATH_CONSOLAS = "fonts/CONSOLA.ttf";
};
