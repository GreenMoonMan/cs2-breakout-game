#ifndef BALL_H
#define BALL_H

#include "Common.h"
#include "Collision.h"
#include "Physics.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>


class Ball : public Collision
{
	public:
		//TODO fix to add initial positon
		//maybe have the velocity as a different function
		Ball(double diameter, double xVel, double yVel);
		Ball(double diameter);
		virtual ~Ball();

		//redefinitions
		virtual void update(const sf::Clock clock) override;
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;

		class CollisionError
		{
			public:
				CollisionError(std::string e);
				std::string what();

			private:
				std::string _e;
		};

	
	private:
		double _xVel, _yVel;
		Collision* _prevXCol;
		Collision* _prevYCol;
		sf::CircleShape* _ballShape;

		//functions
		//changes angle of the ball (in degrees)
		void changeDirection(double angle);
		sf::Vector2f hitboxOverlap(Collision* obj1, Collision* obj2);
};


#endif