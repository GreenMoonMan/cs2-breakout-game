#include "Collision.h"
#include "Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

//constructors
Collision::Collision(double x, double y, double width, double height)
: _pos(x, y), _hitbox(width, height)
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
	return _hitbox.width;
}


double Collision::getHbHeight() const
{
	return _hitbox.height;
}


Position Collision::getPosition() const
{
	return _pos;
}


Size Collision::getHitbox() const
{
	return _hitbox;
}


//dummy virtual function, derived classes don't need to implement this
void Collision::update()
{ }


//***************************************************************************************************
//friend functions
//***************************************************************************************************

sf::RectangleShape drawHitbox(Collision &obj)
{
	sf::Vector2f hitBoxSize = obj._hitbox.transformToScreen();
	sf::RectangleShape returnRect(hitBoxSize);

	//move to correcto position
	sf::Vector2f screenPos = obj._pos.transformToScreen(obj._hitbox);
	returnRect.setPosition(screenPos);

	//set fill color of hitbox to transperent
	returnRect.setFillColor(sf::Color(0, 0, 0, 0));

	//set up outline
	returnRect.setOutlineColor(sf::Color::Red);
	returnRect.setOutlineThickness(2);

	return returnRect;
}


bool checkCollision(Collision *obj1, Collision *obj2)
{

}

