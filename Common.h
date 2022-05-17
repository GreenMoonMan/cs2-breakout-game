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

	// const unsigned SCREEN_WIDTH = 1600;
	const unsigned SCREEN_WIDTH = 1920;
	// const unsigned SCREEN_HEIGHT = 900;
	const unsigned SCREEN_HEIGHT = 1080;

	//blocks
	const int BLOCKS_ROWS = 3;
	const int BLOCKS_COLUMNS = 8;
	const double BLOCKS_HEIGHT = 4;
	const double BLOCKS_WIDTH_VARIANCE = 2;
	const double BLOCK_BALL_SPEED_INCREASE = 20;

	//paddle
	//in degrees
	const double MAX_BALL_PADDLE_DEFLECTION = 50;

	//ball
	const int BALL_STARTING_SPEED = 70;

}

#endif
