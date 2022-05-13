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
	//create paddle
	paddle = new Paddle(Size(30, 1));
	gameObjects.push_back(paddle);

	//create ball
	//dummy lauch value, change to be random later
	ball = new Ball(2, 55, 55);
	gameObjects.push_back(ball);

	//test creation of blocks
	for(int row = 0; row < 3; row++)
	{
		double avWidth = gameConstants::MAX_X / 6;
		double usedWidth = 0;

		//create everything except the last object
		for(int i = 0; i < 6; i++)
		{
			double width = avWidth;
			double height = gameConstants::BLOCKS_HEIGHT;
			double yPos = 50 + row * gameConstants::BLOCKS_HEIGHT;

			Position pos(usedWidth + width/2, yPos);

			Block* blockPtr = new Block(pos, Size(width, height), 0);
			gameObjects.push_back(blockPtr);

			usedWidth += width;
		}
	}
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
}


//--------------------------------------------------------------------------------

void BreakoutGame::display()
{
	for(Collision* object : gameObjects)
	{
		renderWindow.draw(*object->draw());
		renderWindow.draw(drawHitbox(object));
	}
}


//***************************************************************************************************
//other methods
//***************************************************************************************************

bool BreakoutGame::isGameOver()
{
	return gameOver;
}


bool BreakoutGame::getScore()
{
	return score;
}

