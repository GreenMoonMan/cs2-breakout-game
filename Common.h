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
	const int BLOCKS_ROWS = 4;
	const int BLOCKS_COLUMNS = 10;
	const double BLOCKS_HEIGHT = 4;
	const double BLOCKS_BASE_HEIGHT = 50;
	const double BLOCKS_WIDTH_VARIANCE = 5;
	const double BLOCK_BALL_SPEED_INCREASE = 10;

	//paddle
	//in degrees
	const double PADDLE_WIDTH = 30;
	const double PADDLE_HEIGHT = 0.8;
	const double MAX_BALL_PADDLE_DEFLECTION = 60;
	const double PADDLE_SPEED = 105;

	//ball
	const double BALL_DIAMETER = 2;
	const double BALL_STARTING_SPEED = 70;
	const double BALL_STARTING_X = 80;
	const double BALL_STARTING_Y = 10;
	const double BALL_LAUNCH_ANGLE_DEVIATION = 85;
	const double BALL_LAUNCH_DELAY = 1.5; //in seconds
	const int BALLS_AVAILABLE = 3;
}

#endif
