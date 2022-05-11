#include "Block.h"
#include "Ball.h"
#include "Collision.h"
#include <cstddef>

Block::Block(Position position, Size size, double multiplier)
:	Collision(position, size),
	_speedMultiplier(multiplier), _destroyed(false),
	_blockShape(new sf::RectangleShape(hitbox.transformToScreen()))
{

}


Block::~Block()
{
	delete _blockShape;
	_blockShape = nullptr;
}


//--------------------------------------------------------------------------------
//methods
void Block::setColor(sf::Color color)
{
	_blockShape->setFillColor(color);
}


bool Block::isDestroyed() const
{
	return _destroyed;
}


double Block::getSpeedMultiplier() const
{
	return _speedMultiplier;
}


//--------------------------------------------------------------------------------
//redefinitions

//TODO currently this is a dummy and can be removed 
void Block::update(const sf::Clock)
{ }


void Block::collisionAction(Collision* otherObj)
{
	Ball* ballPtr = dynamic_cast<Ball*>(otherObj);

	if(ballPtr != nullptr)
	{
		//ball destorys the block
		_destroyed = true;

		//move the block off screen so that it doens't interfere with the ball
		pos.x = -hitbox.width;
	}
}


sf::Drawable* Block::draw()
{
	_blockShape->setPosition(pos.transformToScreen(hitbox));
	return _blockShape;
}

