#ifndef COLLISION_H
#define COLLISION_H

#include "Physics.h"
#include "Common.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Collision
{
	public:
		//constructors
		Collision(double x, double y, double width, double height);
		Collision(double x, double y);
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
		virtual void update();

		//TODO make abstract
		//abstract function
		virtual void collisionAction(const Collision*);
		virtual sf::Drawable* draw();

		//friends
		friend sf::RectangleShape drawHitbox(Collision& obj);
		friend bool checkCollision();

		//TODO move into protected
		Position _pos;
		Size _hitbox;

	protected:
};


//functions
sf::RectangleShape drawHitbox(Collision& obj);
bool checkCollision(Collision* obj1, Collision* obj2);


#endif
