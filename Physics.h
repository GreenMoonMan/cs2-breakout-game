#ifndef PHYSICS_H
#define PHYSICS_H

#include "Common.h"

#include <SFML/System/Vector2.hpp>

/************************************************************************************************************************
* This file contains multiple classes responsible for the position and size of objects
*
* note about coordinates:
*	in game coordinates are in the first quadrant of a cartesian plane with the origin at the bottom left of the screen
*	they range from 0-160 on the x and 0-90 on the y
*	for every object in the game, the coordinates are taken to be from the center of the object
*	
*	screen coordinates start in the top left with y increasing as you move lower and x increasing as you move to the right
*	the screen can also have varying width and height, as the unit of measurement is pixels
*	screen coordinates for an object are take to be from the top left corner of an object
*	
*	the transformToScreen methods in are used to translate from in game coordinates to screen coordinates
************************************************************************************************************************/



/********************************************************************************
* Size
*
* stores the size of an object using width and height
* the constructor can be used to supply an objects width and height
* but if no values are supplied, the default width and height are both zero
*
* 2 Size objects can be compared with each other,
* doing so compares the area taken up by each object
********************************************************************************/

class Size 
{
	public:
		Size(double objectWidth, double objectHeight);
		Size();

		double width;
		double height;

		//overloads, compares area of two Size objects
		bool operator==(const Size& otherObj) const;
		bool operator!=(const Size& otherObj) const;

		bool operator<(const Size& otherObj) const;
		bool operator<=(const Size& otherObj) const;
		bool operator>(const Size& otherObj) const;
		bool operator>=(const Size& otherObj) const;

		//transforms from in game size to screen size in pixels
		sf::Vector2f transformToScreen() const;
};



/********************************************************************************
* Position
*
* stores the position of an object in game coordinates
* the constructor can be used to initialize the position
* if no values are given, the default position is at (0, 0)
* 
* transformToScreen methods are used to tran
********************************************************************************/

class Position
{
	public:
		Position(double xPos, double yPos);
		Position();

		double x;
		double y;

		//transforms from in game coordinates to screen coordinates
		//if an object with size is given, it will take into account the
		//difference in centers of an object in game coordinates vs one in screen coordinates
		sf::Vector2f transformToScreen() const;
		sf::Vector2f transformToScreen(const Size& objSize) const;
};



/********************************************************************************
* PolarVector
*
* represents a vector in polar coordinates
* can convert to and from cartesian coordinates using the provided methods
********************************************************************************/

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




#endif
