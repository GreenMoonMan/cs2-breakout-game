#ifndef COLLISION_H
#define COLLISION_H

#include "Physics.h"
#include "Common.h"
#include <SFML/Graphics/RectangleShape.hpp>


class Collision
{
	public:
		//constructors
		Collision(double x, double y, double width, double height);
		Collision(double x, double y);
		Collision();

		//getters
		double getX() const;
		double getY() const;
		double getHbWidth() const;
		double getHbHeight() const;

		//abstract function
		// virtual void collisionAction(const Collision&) = 0;

		//friends
		friend sf::RectangleShape drawHitbox(Collision& obj);

	protected:
		Position _pos;
		//hitbox size
		double _width, _height;
};


sf::RectangleShape drawHitbox(Collision& obj);


#endif
