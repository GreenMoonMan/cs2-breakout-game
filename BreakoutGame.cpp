#include "BreakoutGame.h"
#include "Ball.h"
#include "Block.h"
#include "Collision.h"
#include "Common.h"
#include "Paddle.h"
#include "Physics.h"
#include "Wall.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>


BreakoutGame::BreakoutGame(sf::RenderWindow& window)
:	renderWindow(window),
	score(0), gameOver(false),
	launchBall(false), ballLaunchTimer(0), ballsLeft(gameConstants::BALLS_AVAILABLE), win(false),
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
	paddle = new Paddle(Size(gameConstants::PADDLE_WIDTH, gameConstants::PADDLE_HEIGHT));
	gameObjects.push_back(paddle);

	//FIXME breaks for position values of -10
	//prep for launching ball
	//create dummy ball
	ball = new Ball(gameConstants::BALL_DIAMETER, PolarVector(0, 0), Position(gameConstants::BALL_STARTING_X, gameConstants::BALL_STARTING_Y));
	// ball = new Ball(2, PolarVector(20, 90), Position(10, 10));
	gameObjects.push_back(ball);
	launchBall = true;
	ballLaunchTimer = 0;

	
	createBlocks();

	if(GAMEPLAY_DEBUG)
		std::cout << "ball loc: " << searchForType<Ball>() << std::endl;
}


//--------------------------------------------------------------------------------

void BreakoutGame::run(const sf::Clock& clock)
{
	//launch ball when ready
	if(launchBall && ballLaunchTimer >= gameConstants::BALL_LAUNCH_DELAY)
	{
		launchNewBall();
		
		launchBall = false;
	}

	ballLaunchTimer += clock.getElapsedTime().asSeconds();

	//only run game after the ball has finished launching
	if(!launchBall)
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
				// ball->collisionAction(&tempWall);
			}
		}


		//key presses
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			paddle->move(gameConstants::PADDLE_SPEED);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			paddle->move(-gameConstants::PADDLE_SPEED);
		}


		//update all objects
		for(Collision* obj : gameObjects)
		{
			obj->update(clock);
		}

		//update score
		score = Block::blocksDestroyed;
		

		if(ball->getPosition().y + ball->getHitbox().height/4 < 0 && !launchBall)
		{
			ballsLeft--;

			if(ballsLeft == 0)
			{
				gameOver = true;
			}

			else
			{
				launchBall = true;
				ballLaunchTimer = 0;
			}
		}

		//if the game is won
		if(Block::blocksDestroyed == Block::numOfBlocks)
		{
			gameOver = true;
			win = true;
		}
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


bool BreakoutGame::isGameWon()
{
	return win;
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



void BreakoutGame::launchNewBall()
{
	double launchAngle = (static_cast<double>(std::rand()) / RAND_MAX) * gameConstants::BALL_LAUNCH_ANGLE_DEVIATION;
	//set middle to be vertical
	launchAngle += 90 - gameConstants::BALL_LAUNCH_ANGLE_DEVIATION/2.0;

	PolarVector launchVel(gameConstants::BALL_STARTING_SPEED, launchAngle);
	//place right above the paddle
	Position launchPos(paddle->getPosition().x, gameConstants::BALL_STARTING_Y);

	Ball* newBall = new Ball(gameConstants::BALL_DIAMETER, launchVel, launchPos);

	//delete old ball and use the new one
	int ballIndex = searchForType<Ball>();
	gameObjects.at(ballIndex) = newBall;
	delete ball;
	ball = newBall;
}



