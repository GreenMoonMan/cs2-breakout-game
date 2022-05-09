#include "Wall.h"
#include "Collision.h"
#include "Common.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


// constructor/destructor

Wall::Wall(Side location)
: _location(location), _dummyRect(new(sf::RectangleShape))
{
	//set position to the appropriate wall
	if(location == LEFT || location == RIGHT)
	{
		hitbox.width = 0;
		hitbox.height = gameConstants::MAX_Y;
		pos.y = gameConstants::MAX_Y / 2;

		if(location == RIGHT)
		{
			//move to right side of the screen
			pos.x = gameConstants::MAX_X;
		}
	}

	else if(location == TOP || location == BOTTOM)
	{
		hitbox.width = gameConstants::MAX_X;
		hitbox.height = 0;
		pos.x = gameConstants::MAX_X / 2;

		if(location == TOP)
		{
			//move to the top of the screen
			pos.y = gameConstants::MAX_Y;
		}
	}

	//so that nothing gets displayed
	_dummyRect->setFillColor(sf::Color::Transparent);
}


Wall::~Wall()
{
	delete _dummyRect;
	_dummyRect = nullptr;
}


//--------------------------------------------------------------------------------
//methods


Wall::Side Wall::getSide() const
{
	return _location;
}


//--------------------------------------------------------------------------------
//redefinitions

//empty
void collisionAction(Collision*)
{ }


sf::Drawable* draw()
{
	
}


