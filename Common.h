#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>


const bool GAMEPLAY_DEBUG = false;
const bool INTERFACE_DEBUG = true;
const unsigned MAX_FRAMERATE = 75*3;


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
	const sf::Color BLOCK_COLORS[BLOCKS_ROWS] =
		{
			sf::Color::Blue, sf::Color::Green, sf::Color::Magenta, sf::Color::Red
		};

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
	const double BALL_LAUNCH_DELAY = 1.25; //in seconds
	const int BALLS_EXTRA_AVAILABLE = 3;
}


namespace MenuConstants
{
	const std::string SCORE_FILE_PATH = "scores.txt";
	const std::string FONT_FILE_PATH = "assets/Monoid-Regular.ttf";
}



#endif
