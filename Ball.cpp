#include "Ball.h"
#include "Collision.h"
#include "Physics.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cmath>
#include <string>


Ball::Ball(double diameter, double xVel, double yVel)
:	Collision(10, 10, diameter, diameter),
	_xVel(xVel), _yVel(yVel),
	_prevXCol(nullptr), _prevYCol(nullptr),
	_ballShape(new sf::CircleShape())
{ 
	//set correct size
	_ballShape->setRadius(hitbox.transformToScreen().x / 2);
}


Ball::Ball(double diameter)
:	Ball(diameter, 0, 0)
{ }


Ball::~Ball()
{
	delete _ballShape;
	_ballShape = nullptr;
}


//--------------------------------------------------------------------------------
//redefinitions

void Ball::update(const sf::Clock clock)
{
	//move the ball
	pos.x += _xVel * clock.getElapsedTime().asSeconds();
	pos.y += _yVel * clock.getElapsedTime().asSeconds();
}


void Ball::collisionAction(Collision* otherObj)
{
	sf::Vector2f overlap = hitboxOverlap(this, otherObj);

	//hits the side
	//and prevent hitting the same object twice
	if(overlap.x < overlap.y && _prevXCol != otherObj)
	{
		//"bounce" sideways
		_xVel *= -1;
		_prevXCol = otherObj;
	}

	else if(overlap.x > overlap.y && _prevYCol != otherObj)
	{
		//"bounce" vertically
		_yVel *= -1;
		_prevYCol = otherObj;
	}
}


sf::Drawable* Ball::draw()
{
	//update postion
	_ballShape->setPosition(pos.transformToScreen(hitbox));
	return _ballShape;
}


//--------------------------------------------------------------------------------
//private methods

sf::Vector2f Ball::hitboxOverlap(Collision* obj1, Collision* obj2)
{
	sf::Vector2f overlapVect;

	double avX = (obj1->getHitbox().width + obj2->getHitbox().width) / 2;
	double distanceX = std::abs(obj1->getPosition().x - obj2->getPosition().x);
	overlapVect.x = avX - distanceX;

	double avY = (obj1->getHitbox().height + obj2->getHitbox().height) / 2;
	double distanceY = std::abs(obj1->getPosition().y - obj2->getPosition().y);
	overlapVect.y = avY - distanceY;

	//the overlap distance can never be negative, throw error if so
	if(overlapVect.x < 0 || overlapVect.y < 0)
	{
		std::string errorMesg = "Overlap distance negative (x: ";
		errorMesg += std::to_string(overlapVect.x) + ", y: " + std::to_string(overlapVect.y);
		errorMesg += ")";

		throw CollisionError(errorMesg);
	}

	return overlapVect;
}


//--------------------------------------------------------------------------------
//CollisionError

Ball::CollisionError::CollisionError(std::string e)
: _e(e)
{ }


std::string Ball::CollisionError::what()
{
	return _e;
}

