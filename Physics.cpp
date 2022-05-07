#include "Physics.h"
#include "Common.h"

//position struct
Position::Position(double xPos, double yPos)
: x(xPos), y(yPos)
{ }

Position::Position()
: Position(0, 0)
{ }

//***************************************************************************************************

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

