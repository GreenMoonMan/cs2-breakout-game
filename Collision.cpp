#include "Collision.h"
#include "Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

//constructors
Collision::Collision(double x, double y, double width, double height)
: _pos(x, y), _width(width), _height(height)
{ }


Collision::Collision(double x, double y)
: Collision(x, y, 0, 0)
{ }


Collision::Collision()
: Collision(0, 0, 0, 0)
{ }



//getters
double Collision::getX() const
{
	return _pos.x;
}


double Collision::getY() const
{
	return _pos.y;
}


double Collision::getHbWidth() const
{
	return _width;
}


double Collision::getHbHeight() const
{
	return _height;
}


//***************************************************************************************************
//friend functions
//***************************************************************************************************

sf::RectangleShape drawHitbox(Collision &obj)
{
	sf::Vector2f hitBoxSize(obj._width, obj._height);
	sf::RectangleShape returnRect(hitBoxSize);

	Position screenPos = translatePosition(obj._pos, 1920, 1080);
	returnRect.setPosition(screenPos.x, screenPos.y);

	//set fill color of hitbox to transperent
	returnRect.setFillColor(sf::Color(0, 0, 0, 0));

	//set up outline
	returnRect.setOutlineColor(sf::Color::Red);
	returnRect.setOutlineThickness(3);

	return returnRect;
}

