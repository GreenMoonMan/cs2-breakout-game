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
		Position getPosition() const;
		Size getHitbox() const;

		//abstract function
		// virtual void collisionAction(const Collision&) = 0;

		//friends
		friend sf::RectangleShape drawHitbox(Collision& obj);

		//TODO move into protected
		Position _pos;
		Size _hitbox;

	protected:
};


sf::RectangleShape drawHitbox(Collision& obj);


#endif
