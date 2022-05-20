#include "Common.h"

#include "Physics.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>


using namespace std;


//***************************************************************************************************
//size class
//***************************************************************************************************

Size::Size(double objectWidth, double objectHeight)
: width(objectWidth), height(objectHeight)
{ }


Size::Size()
: Size(0, 0)
{ }


//------------------------------------------------------------
//overloads


bool Size::operator==(const Size& otherObj) const
{
	double thisArea = width * height;
	double otherArea = otherObj.width * otherObj.height;

	if(thisArea == otherArea)
	{
		return true;
	}

	else  
	{
		return false;
	}
}


bool Size::operator!=(const Size &otherObj) const
{
	return !(*this == otherObj);
}


bool Size::operator<(const Size& otherObj) const
{
	double thisArea = width * height;
	double otherArea = otherObj.width * otherObj.height;

	if(thisArea < otherArea)
	{
		return true;
	}

	else  
	{
		return false;
	}
}


bool Size::operator<=(const Size& otherObj) const
{
	return *this < otherObj || *this == otherObj;
}


bool Size::operator>(const Size& otherObj) const
{
	return otherObj < *this; 
}


bool Size::operator>=(const Size& otherObj) const
{
	return !(*this < otherObj);
}


//------------------------------------------------------------

sf::Vector2f Size::transformToScreen() const
{
	sf::Vector2f returnVect;

	//scale width and height based on screen size
	returnVect.x = width * gameConstants::SCREEN_WIDTH / gameConstants::MAX_X;
	returnVect.y = height * gameConstants::SCREEN_HEIGHT / gameConstants::MAX_Y;

	return returnVect;
}



//***************************************************************************************************
//position class
//***************************************************************************************************

//constructors
Position::Position(double xPos, double yPos)
: x(xPos), y(yPos)
{ }

Position::Position()
: Position(0, 0)
{ }


//transforms
sf::Vector2f Position::transformToScreen() const
{
	sf::Vector2f returnVect;

	//scale
	returnVect.x = x * gameConstants::SCREEN_WIDTH / gameConstants::MAX_X;
	returnVect.y = y * gameConstants::SCREEN_HEIGHT / gameConstants::MAX_Y;

	//translate y
	returnVect.y = gameConstants::SCREEN_HEIGHT - returnVect.y;

	return returnVect;
}


sf::Vector2f Position::transformToScreen(const Size& objSize) const
{
	sf::Vector2f returnVect = transformToScreen();
	sf::Vector2f sizeVect = objSize.transformToScreen();

	//in game position is from the center of the object,
	//but the screen coordinates have the coordinates from the top left of the object
	//need to translate from the center to the top left
	returnVect.x -= sizeVect.x/2;
	returnVect.y -= sizeVect.y/2;

	return returnVect;
}


//***************************************************************************************************
//PolarVector class
//***************************************************************************************************

PolarVector::PolarVector(double mag, double theta)
: magnitude(mag), angle(theta)
{ }


PolarVector::PolarVector()
: PolarVector(0, 0)
{ }


//transforms
void PolarVector::fromCartesian(double x, double y)
{
	//get angle
	angle = std::atan2(y, x);
	//convert to degrees
	angle *= 180 / M_PI;

	magnitude = std::sqrt(x*x + y*y);
}


void PolarVector::fromCartesian(sf::Vector2f vect)
{
	fromCartesian(vect.x, vect.y);
}


sf::Vector2f PolarVector::toCartesian() const
{
	sf::Vector2f returnVect;
	double radians = angle * M_PI / 180.0;

	returnVect.x = magnitude * cos(radians);
	returnVect.y = magnitude * sin(radians);

	return returnVect;
}



