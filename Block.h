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
		Block(Position position, Size size, double speed);
		virtual ~Block();

		//methods
		void setColor(sf::Color color);
		bool isDestroyed() const;
		double getSpeedNewSpeed() const;

		//redefinitions
		virtual void update(const sf::Clock) override;
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;

		//static attributes
		//probably move into private later
		static int numOfBlocks;
		static int blocksDestroyed;


	private:
		double _newSpeed;
		bool _destroyed;
		sf::RectangleShape* _blockShape;
};


#endif
