#ifndef BLOCK_H
#define BLOCK_H

#include "Collision.h"
#include "../Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


/***************************************************************************************************
* Block
*
* The blocks that the ball with hit in the game
* the constructor can set the initial position, initial size
* and the speed that it will set the ball to when the ball hits it
*
* when a block is hit it will be "destroyed", it will be moved off screen and won't be able to be interacted with
* 
* there are 3 static attributes:
*		numOfBlocks is the number of block created,
*		will automatically increase/decrease as blocks are created/deleted
*
*		blocksDestroyed: the number of block that have been destroyed (hit by the ball)
*		will automatically increase/decrease as blocks are created/deleted
*
*		score: will increase when a block is destroyed
*		does NOT automatically reset to 0 when a new game is started
***************************************************************************************************/


class Block : public Collision
{
	public:
		Block(Position position, Size size, double speed);
		virtual ~Block();

		//methods
		void setColor(sf::Color color);
		void setSpeed(double speed);
		bool isDestroyed() const;
		double getSpeedNewSpeed() const;


		//collisionAction must be called after the ball's collision action, else there will be a collision error
		virtual void collisionAction(Collision* otherObj) override;
		virtual sf::Drawable* draw() override;

		//static getters
		static int getNumOfBlocks();
		static int getBlocksDestroyed();

		//game's score based solely on how many blocks were destroyed
		static int score;


	private:
		double _newSpeed;
		bool _destroyed;
		sf::RectangleShape* _blockShape;

		//static attributes
		static int _blocksDestroyed;
		static int _numOfBlocks;
};


#endif
