#ifndef COLLISION_H
#define COLLISION_H

#include "../Common.h"
#include "../Physics.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

/********************************************************************************
* Collision Class
*
* A base abstract class that handles physics and collisions
* every in game object is derived from this class
* this way collision physics can be self contained for every object
********************************************************************************/


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
		Position getPosition() const;
		Size getHitbox() const;

		//implementation in derived classes is optional
		//by default this function does nothing
		virtual void update(const sf::Clock);


		//------------------------------------------------------------
		//abstract functions
		//the derived class is responsible for implementing this function
		//it will be called after a collision is detected
		//with the other parameter being the object that was collided with
		virtual void collisionAction(Collision*) = 0;
		//every object in the game will also poses something that can be drawn on the screen
		virtual sf::Drawable* draw() = 0;


		//friends
		//returns a red box that represents the hitbox for an object
		friend sf::RectangleShape drawHitbox(Collision* obj);
		//checks if 2 objects have collided
		friend bool checkCollision(Collision* obj1, Collision* obj2);


	protected:
		Position pos;
		Size hitbox;
};


#endif
