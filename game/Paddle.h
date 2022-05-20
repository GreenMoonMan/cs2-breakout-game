#ifndef PADDLE_H
#define PADDLE_H

#include "../Common.h"
#include "../Physics.h"

#include "Collision.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


/***************************************************************************************************
* Paddle
* 
* the user interactable paddle at the bottom of the screen
* the constructor allows setting the size and position,
* if the position is not given, it will automatically be put at the bottom middle of the screen
*
* the move() method will move the paddle at the desired speed
* will only move the paddle when repeatedly called, paddle will stop when not called
***************************************************************************************************/


class Paddle : public Collision
{
	public:
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
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;
		
	
	private:
		double _velocity;
		Size& _paddleSize;
		sf::RectangleShape* _paddleShape;
};


#endif
