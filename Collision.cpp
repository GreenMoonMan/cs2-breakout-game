#include "Collision.h"
#include "Physics.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

//constructors
Collision::Collision(double x, double y, double width, double height)
: pos(x, y), hitbox(width, height)
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
	return pos.x;
}


double Collision::getY() const
{
	return pos.y;
}


double Collision::getHbWidth() const
{
	return hitbox.width;
}


double Collision::getHbHeight() const
{
	return hitbox.height;
}


Position Collision::getPosition() const
{
	return pos;
}


Size Collision::getHitbox() const
{
	return hitbox;
}


//dummy virtual function, derived classes don't need to implement this
void Collision::update()
{ }


//***************************************************************************************************
//friend functions
//***************************************************************************************************

sf::RectangleShape drawHitbox(Collision* obj)
{
	sf::Vector2f hitBoxSize = obj->hitbox.transformToScreen();
	sf::RectangleShape returnRect(hitBoxSize);

	//move to correcto position
	sf::Vector2f screenPos = obj->pos.transformToScreen(obj->hitbox);
	returnRect.setPosition(screenPos);

	//set fill color of hitbox to transperent
	returnRect.setFillColor(sf::Color::Transparent);

	//set up outline
	returnRect.setOutlineColor(sf::Color::Red);
	returnRect.setOutlineThickness(2);

	return returnRect;
}


bool checkCollision(Collision *obj1, Collision *obj2)
{
	double distanceX = std::abs(obj1->getPosition().x - obj2->getPosition().x);
	double distanceY = std::abs(obj1->getPosition().y - obj2->getPosition().y);
	double avWidth = (obj1->getHitbox().width + obj2->getHitbox().width)/2;
	double avHeight= (obj1->getHitbox().height + obj2->getHitbox().height)/2;

	if(distanceX < avWidth && distanceY < avHeight)
	{
		return true;
	}

	else
	{
		return false;
	}
}

