#include "Paddle.h"
#include "Collision.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>

//constructors
Paddle::Paddle(Position paddlePos, Size paddleSize)
: Collision(paddlePos, paddleSize), _velocity(0),
	_paddleShape(new sf::RectangleShape(sf::Vector2f(paddleSize.transformToScreen())))
{ 
	//TODO this may not even be neccessary since it is calculated in the draw action
	_paddleShape->setPosition(paddlePos.transformToScreen());
	_paddleShape->setFillColor(sf::Color::Green);
}



Paddle::~Paddle()
{
	delete _paddleShape;
	_paddleShape = nullptr;
}


//--------------------------------------------------------------------------------
//methods
void Paddle::move(double velocity)
{
	_velocity = velocity;
}


//--------------------------------------------------------------------------------
//redefinitions
void Paddle::update(const sf::Clock clock)
{
	pos.x += _velocity * clock.getElapsedTime().asSeconds();
}


//dummy function, does nothing
void Paddle::collisionAction(Collision*)
{ }


sf::Drawable* Paddle::draw()
{
	return _paddleShape;
}


