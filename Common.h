#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


const bool GAMEPLAY_DEBUG = true;


namespace gameConstants
{
	const double MAX_X = 160;
	const double MAX_Y = 90;

	const unsigned SCREEN_WIDTH = 1600;
	// const unsigned SCREEN_WIDTH = 1920;
	const unsigned SCREEN_HEIGHT = 900;
	// const unsigned SCREEN_HEIGHT = 1080;

	//blocks
	const int BLOCKS_ROWS = 3;
	const double BLOCKS_HEIGHT = 8;
	const double BLOCKS_MIN_WIDTH = 10;
	const double BLOCKS_MAX_WIDTH = 20;

	//paddle
	//in degrees
	const double MAX_BALL_PADDLE_DEFLECTION = 50;
}

#endif
