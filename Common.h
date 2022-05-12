#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


namespace gameConstants
{
	const double MAX_X = 160;
	const double MAX_Y = 90;

	const unsigned SCREEN_WIDTH = 1280;
	const unsigned SCREEN_HEIGHT = 720;

	//blocks
	const int BLOCKS_ROWS = 3;
	const double BLOCKS_HEIGHT = 10;
	const double BLOCKS_MIN_WIDTH = 10;
	const double BLOCKS_MAX_WIDTH = 20;

	//paddle
	//in degrees
	const double MAX_BALL_PADDLE_DEFLECTION = 40;
}

#endif
