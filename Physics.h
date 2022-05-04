#ifndef PHYSICS_H
#define PHYSICS_H

#include "Common.h"
#include <SFML/System/Vector2.hpp>


struct Position
{
	Position(double xPos, double yPos);
	Position();

	double x;
	double y;
};


//***************************************************************************************************
/*
*	translatePosition()
*	this function translates in game coordinates to screen coordinates
*	
*	in game coordinates are in the first quadrant of a cartesian plane with the origin at the bottom left of the screen
*	they range from 0-160 on the x and 0-90 on the y
*	
*	screen coordinates start in the top left with y increasing as you move lower and x increasing as you move to the right
*	the screen can also have varying width and height
*/

Position translatePosition(const Position& pos, const unsigned screenWidth, const unsigned screenHeight);



#endif
