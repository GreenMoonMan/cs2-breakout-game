#ifndef BALL_H
#define BALL_H

#include "../Common.h"
#include "../Physics.h"
#include "Collision.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>


/***************************************************************************************************
* Ball
*
* Ball object for the game
* the constructor takes in the size of the ball and the initial velocity
* optionalally can give an initial position too.
***************************************************************************************************/


class Ball : public Collision
{
	public:
		//defaults to position (10, 10)
		//can specify inital velocity in xy or polar
		Ball(double diameter, double xVel, double yVel);
		Ball(double diameter, PolarVector initialVelocity);
		Ball(double diameter, PolarVector initialVelocity, Position initialPos);
		Ball(double diameter);
		virtual ~Ball();

		//redefinitions
		virtual void update(const sf::Clock clock) override;
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;

		//thrown if there is an error calculating collisions, useful for debugging
		class CollisionError
		{
			public:
				CollisionError(std::string e);
				std::string what();

			private:
				std::string _e;
		};

	
	private:
		//velocity of the ball
		double _xVel, _yVel;
		//used to prevent registering 2 collisions with the same object
		Collision* _prevXCol;
		Collision* _prevYCol;
		sf::CircleShape* _ballShape;

		//functions
		//changes angle of the ball (in degrees)
		void changeDirection(double angle);
		void setSpeed(double speed);
		//returns how much the hitboxes of 2 objects overlap
		//is used to determine whether the ball should bounce sideways, or vertically
		sf::Vector2f hitboxOverlap(Collision* obj1, Collision* obj2) const;
};


#endif