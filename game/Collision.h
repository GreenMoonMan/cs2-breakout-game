#ifndef COLLISION_H
#define COLLISION_H

#include "../Common.h"

#include "Physics.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


class Collision
{
	public:
		//constructors
		Collision(double x, double y, double width, double height);
		Collision(double x, double y);
		Collision(Position colPos);
		Collision(Position colPos, Size hbSize);
		Collision();

		virtual ~Collision();

		//getters
		double getX() const;
		double getY() const;
		double getHbWidth() const;
		double getHbHeight() const;
		Position getPosition() const;
		Size getHitbox() const;

		//implementation in derived classes is optional
		//by default this function does nothing
		virtual void update(const sf::Clock);

		//abstract functions
		virtual void collisionAction(Collision*) = 0;
		virtual sf::Drawable* draw() = 0;

		//friends
		friend sf::RectangleShape drawHitbox(Collision* obj);
		friend bool checkCollision(Collision* obj1, Collision* obj2);


	protected:
		Position pos;
		Size hitbox;
};


#endif
