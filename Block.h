#ifndef BLOCK_H
#define BLOCK_H

#include "Collision.h"
#include "Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


class Block : public Collision
{
	public:
		Block(Position position, Size size, double multiplier);
		virtual ~Block();

		//methods
		void setColor(sf::Color color);
		bool isDestroyed() const;
		double getSpeedMultiplier() const;

		//redefinitions
		virtual void update(const sf::Clock) override;
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;


	private:
		double _speedMultiplier;
		bool _destroyed;
		sf::RectangleShape* _blockShape;
};


#endif