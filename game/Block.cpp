#include "../Common.h"

#include "Block.h"
#include "Ball.h"
#include "Collision.h"
#include <SFML/Graphics/Color.hpp>
#include <cstddef>


int Block::numOfBlocks = 0;
int Block::blocksDestroyed = 0;
int Block::score = 0;

//--------------------------------------------------------------------------------

Block::Block(Position position, Size size, double multiplier)
:	Collision(position, size),
	_newSpeed(multiplier), _destroyed(false),
	_blockShape(new sf::RectangleShape(hitbox.transformToScreen()))
{
	_blockShape->setOutlineColor(sf::Color::Black);
	_blockShape->setOutlineThickness(1);
	numOfBlocks++;
}


Block::~Block()
{
	delete _blockShape;
	_blockShape = nullptr;

	//reset the block counters
	numOfBlocks--;
	
	if(_destroyed)
	{
		blocksDestroyed--;
	}
}


//--------------------------------------------------------------------------------
//methods
void Block::setColor(sf::Color color)
{
	_blockShape->setFillColor(color);
}


void Block::setSpeed(double speed)
{
	_newSpeed = speed;
}


bool Block::isDestroyed() const
{
	return _destroyed;
}


double Block::getSpeedNewSpeed() const
{
	return _newSpeed;
}


//--------------------------------------------------------------------------------
//redefinitions

//TODO currently this is a dummy and can be removed 
void Block::update(const sf::Clock)
{ }


void Block::collisionAction(Collision* otherObj)
{
	Ball* ballPtr = dynamic_cast<Ball*>(otherObj);

	//if a ball collides with the block
	if(ballPtr != nullptr)
	{
		//ball destorys the block
		_destroyed = true;
		blocksDestroyed++;

		//score increment is dependent on the speed of the block
		score += _newSpeed / gameConstants::BLOCK_BALL_SPEED_INCREASE;

		//move the block off screen so that it doens't interfere with the ball
		pos.x = -hitbox.width;
	}
}


sf::Drawable* Block::draw()
{
	_blockShape->setPosition(pos.transformToScreen(hitbox));
	return _blockShape;
}

