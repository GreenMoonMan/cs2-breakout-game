#include "BreakoutGame.h"
#include "Ball.h"
#include "Block.h"
#include "Collision.h"
#include "Common.h"
#include "Paddle.h"
#include "Physics.h"
#include "Wall.h"

#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>


BreakoutGame::BreakoutGame(sf::RenderWindow& window)
:	renderWindow(window),
	score(0), gameOver(false),
	walls{new Wall(Wall::LEFT), new Wall(Wall::RIGHT), new Wall(Wall::TOP)}
{ 
	//add walls to vector
	for(Wall* el : walls)
	{
		gameObjects.push_back(el);
	}
}


BreakoutGame::~BreakoutGame()
{
	//delete all game objects
	for(Collision* object: gameObjects)
	{
		delete object;
	}
}


//***************************************************************************************************
//the main game
//***************************************************************************************************

void BreakoutGame::setup()
{
	//TODO rewrite ball launch and how blocks are created

	//create paddle
	paddle = new Paddle(Size(30, 1));
	gameObjects.push_back(paddle);

	//create ball
	//dummy lauch value, change to be random later
	//was 55, 55
	ball = new Ball(2, PolarVector(70, rand() % 40 + 70));
	gameObjects.push_back(ball);
	
	//test creation of blocks
	createBlocks();
}


//--------------------------------------------------------------------------------

void BreakoutGame::run(const sf::Clock& clock)
{
	//check if ball hit any objects
	for(Collision* obj : gameObjects)
	{
		if(checkCollision(ball, obj))
		{
			ball->collisionAction(obj);
			obj->collisionAction(ball);
		}
	}

	//check if paddle hits the walls
	for(Collision* wall : walls)
	{
		if(checkCollision(paddle, wall))
		{
			paddle->collisionAction(wall);
		}
	}

	//add bottomwall if debug
	if(GAMEPLAY_DEBUG)
	{
		Wall tempWall = Wall(Wall::BOTTOM);
		
		if(checkCollision(ball, &tempWall))
		{
			ball->collisionAction(&tempWall);
		}
	}


	//key presses
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		paddle->move(90);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		paddle->move(-90);
	}


	//update all objects
	for(Collision* obj : gameObjects)
	{
		obj->update(clock);
	}

	//update score
	score = Block::blocksDestroyed;
	
	//check for game over
	if(ball->getPosition().y + ball->getHitbox().height/2 < 0 || Block::blocksDestroyed == Block::numOfBlocks)
	{
		gameOver = true;
	}
}


//--------------------------------------------------------------------------------

void BreakoutGame::display()
{
	for(Collision* object : gameObjects)
	{
		renderWindow.draw(*object->draw());

		if(GAMEPLAY_DEBUG)
		{
			renderWindow.draw(drawHitbox(object));
		}
	}
}


//***************************************************************************************************
//other methods
//***************************************************************************************************

bool BreakoutGame::isGameOver()
{
	return gameOver;
}


int BreakoutGame::getScore()
{
	return score;
}


//--------------------------------------------------------------------------------
//private methods
//--------------------------------------------------------------------------------

void BreakoutGame::createBlocks()
{
	//iterate through rows
	for(int y = 0; y < gameConstants::BLOCKS_ROWS; y++)
	{
		double usedWidth = 0;
		double currentHeight = gameConstants::BLOCKS_BASE_HEIGHT + gameConstants::BLOCKS_HEIGHT*y;
		double currentSpeed = gameConstants::BALL_STARTING_SPEED + gameConstants::BLOCK_BALL_SPEED_INCREASE*y;

		//iterate through each block in a row, except the last
		for(int x = 0; x < gameConstants::BLOCKS_COLUMNS - 1; x++)
		{
			double variance = (static_cast<double>(rand())/RAND_MAX) * gameConstants::BLOCKS_WIDTH_VARIANCE;

			double width = gameConstants::MAX_X / gameConstants::BLOCKS_COLUMNS - gameConstants::BLOCKS_WIDTH_VARIANCE / 2;
			width += variance;

			if(GAMEPLAY_DEBUG)
			{
				std::cout << width << " ";
			}
			
			//create block
			Position blockPos(usedWidth + width/2, currentHeight);
			Size blockSize(width, gameConstants::BLOCKS_HEIGHT);
			Block* newBlock = new Block(blockPos, blockSize, currentSpeed);
			gameObjects.push_back(newBlock);

			//update variables
			usedWidth += width;
		}

		//create the last block with the remaining width
		double width = gameConstants::MAX_X - usedWidth;
		Position blockPos(usedWidth + width/2, currentHeight);
		Size blockSize(width, gameConstants::BLOCKS_HEIGHT);
		Block* newBlock = new Block(blockPos, blockSize, currentSpeed);
		gameObjects.push_back(newBlock);

		if(GAMEPLAY_DEBUG)
		{
			std::cout << width << std::endl;
		}
	}
}




