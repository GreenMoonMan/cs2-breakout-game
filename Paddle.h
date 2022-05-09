#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"
#include "Collision.h"
#include "Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


class Paddle : public Collision
{
	public:
		//TODO change this to only take in size, and x position
		//the paddle will automatcially be placed at the bottom of the screen
		Paddle(Position paddlePos, Size paddleSize);
		Paddle(Size paddleSize);
		virtual ~Paddle();

		//methods
		void setColor(const sf::Color& color);
		//velocity in units/second
		void move(double velocity);
		
		//redefinitions
		virtual void update(const sf::Clock clock) override;
		virtual void collisionAction(Collision*) override;
		virtual sf::Drawable* draw() override;
		
	
	private:
		double _velocity;
		Size& _paddleSize;
		sf::RectangleShape* _paddleShape;
};


#endif
