#include "Physics.h"
#include "Common.h"
#include <SFML/System/Vector2.hpp>


//***************************************************************************************************
//size class
//***************************************************************************************************

Size::Size(double objectWidth, double objectHeight)
: width(objectWidth), height(objectHeight)
{ }


Size::Size()
: Size(0, 0)
{ }



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

//TODO remove redundant function
Position translatePosition(const Position& pos, const unsigned screenWidth, const unsigned screenHeight)
{
	Position returnPos;

	//scale
	returnPos.x = pos.x * screenWidth / gameConstants::MAX_X;
	returnPos.y = pos.y * screenHeight / gameConstants::MAX_Y;

	//transform y
	returnPos.y = screenHeight - returnPos.y;

	return returnPos;
}

