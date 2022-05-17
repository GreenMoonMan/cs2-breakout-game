#ifndef PHYSICS_H
#define PHYSICS_H

#include "Common.h"
#include <SFML/System/Vector2.hpp>



class Size 
{
	public:
		Size(double objectWidth, double objectHeight);
		Size();

		double width;
		double height;

		//TODO actually test these
		//overloads, compares area of two Size objects
		bool operator==(const Size& otherObj);
		bool operator<(const Size& otherObj);
		bool operator<=(const Size& otherObj);
		bool operator>(const Size& otherObj);
		bool operator>=(const Size& otherObj);

		//transforms from in game size to screen size in pixels
		sf::Vector2f transformToScreen() const;
};


class Position
{
	public:
		Position(double xPos, double yPos);
		Position();

		double x;
		double y;

		//transforms from in game coordinates to screen coordinates
		sf::Vector2f transformToScreen() const;
		sf::Vector2f transformToScreen(const Size& objSize) const;
};


class PolarVector
{
	public:
		PolarVector(double mag, double theta);
		PolarVector();

		double magnitude;
		double angle;

		void fromCartesian(double x, double y);
		void fromCartesian(sf::Vector2f vect);
		sf::Vector2f toCartesian() const;
};


//TODO move explanation into Position class
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
