#include "Ball.h"
#include "Collision.h"
#include "Common.h"
#include "Physics.h"
#include "Paddle.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cmath>
#include <math.h>
#include <string>


using namespace std;


Ball::Ball(double diameter, double xVel, double yVel)
:	Collision(10, 10, diameter, diameter),
	_xVel(xVel), _yVel(yVel),
	_prevXCol(nullptr), _prevYCol(nullptr),
	_ballShape(new sf::CircleShape())
{ 
	//set correct size
	_ballShape->setRadius(hitbox.transformToScreen().x / 2);
}


Ball::Ball(double diameter, PolarVector initialVelocity)
: Ball(diameter, 0, 0)
{
	sf::Vector2f cartesianVel = initialVelocity.toCartesian();

	_xVel = cartesianVel.x;
	_yVel = cartesianVel.y;
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
	if(overlap.x <=overlap.y && _prevXCol != otherObj)
	{
		//"bounce" sideways
		_xVel *= -1;
		_prevXCol = otherObj;
	}

	if(overlap.x >= overlap.y && _prevYCol != otherObj)
	{
		//"bounce" vertically
		_yVel *= -1;
		_prevYCol = otherObj;
	}


	//------------------------------------------------------------
	//paddle collisions

	//FIXME prevent multiple collisions with the paddle

	Paddle* paddlePtr = dynamic_cast<Paddle*>(otherObj);

	//check if the ball hit the paddle
	if(paddlePtr != nullptr)
	{
		//the angle of deflection of the ball is proportional to how off-center the hit of the ball was

		//find where on the paddle the ball hit
		//with a positive distance to the left
		double hitDistance = paddlePtr->getPosition().x - pos.x;

		//scale from -1 to 1, having a magnitude of 1 if it hits the edge of the paddle
		hitDistance /= paddlePtr->getHitbox().width + hitbox.width;

		//TODO clean this up a bit and remove debug
		//multiply by the angle to give deflection angle
		cout << "old speed: " << sqrt(_xVel*_xVel + _yVel*_yVel) << endl;
		changeDirection(gameConstants::MAX_BALL_PADDLE_DEFLECTION * hitDistance);
		// PolarVector vel;
		// vel.fromCartesian(_xVel, _yVel);
		// vel.angle += gameConstants::MAX_BALL_PADDLE_DEFLECTION * hitDistance;
		// sf::Vector2f temp = vel.toCartesian();
		// _xVel = temp.x;
		// _yVel = temp.y;

		cout << "new speed: " << sqrt(_xVel*_xVel + _yVel*_yVel) << endl;
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

//FIXME ball slows down after repeated hits
void Ball::changeDirection(double angle)
{
	//change angle to radians
	angle *= M_PI/180.0;

	_xVel = _xVel * std::cos(angle) - _yVel * std::sin(angle);
	_yVel = _yVel * std::cos(angle) + _xVel* std::sin(angle);
}


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

