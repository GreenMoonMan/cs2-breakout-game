#include "Paddle.h"
#include "Wall.h"
#include "Collision.h"
#include "Common.h"
#include "Physics.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>

//constructors
Paddle::Paddle(Position paddlePos, Size paddleSize)
: Collision(paddlePos, paddleSize),
	_velocity(0), _paddleSize(hitbox),
	_paddleShape(new sf::RectangleShape(sf::Vector2f(paddleSize.transformToScreen())))
{ 
	//default color
	_paddleShape->setFillColor(sf::Color::White);
}


Paddle::Paddle(Size paddleSize)
: Paddle(Position(), paddleSize)
{
	//change position to the bottom center of the screen
	pos.x = gameConstants::MAX_X/2.0;
	pos.y = _paddleSize.height/2.0;
}



Paddle::~Paddle()
{
	delete _paddleShape;
	_paddleShape = nullptr;
}


//--------------------------------------------------------------------------------
//methods
void Paddle::setColor(const sf::Color& color)
{
	_paddleShape->setFillColor(color);
}


void Paddle::move(double velocity)
{
	_velocity = velocity;
}


//--------------------------------------------------------------------------------
//redefinitions
void Paddle::update(const sf::Clock clock)
{
	pos.x += _velocity * clock.getElapsedTime().asSeconds();
	_velocity = 0;
}


void Paddle::collisionAction(Collision* otherObj)
{ 
	//if the paddle has hit the sides of the walls, stop
	Wall* wallPtr = dynamic_cast<Wall*>(otherObj);

	if(wallPtr != nullptr)
	{
		Wall::Side colSide = wallPtr->getSide();

		if(colSide == Wall::LEFT)
		{
			//stop at right side of the screen
			pos.x = _paddleSize.width / 2;
		}

		else if(colSide == Wall::RIGHT)
		{
			//stop at left side of screen
			pos.x = gameConstants::MAX_X - _paddleSize.width / 2;
		}
	}
}


sf::Drawable* Paddle::draw()
{
	_paddleShape->setPosition(pos.transformToScreen(_paddleSize));
	return _paddleShape;
}


