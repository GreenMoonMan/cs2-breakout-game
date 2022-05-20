#include "../Common.h"

#include "BreakoutGame.h"
#include "Ball.h"
#include "Block.h"
#include "Collision.h"
#include "Paddle.h"
#include "Physics.h"
#include "Wall.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>


BreakoutGame::BreakoutGame(sf::RenderWindow& window, sf::Font& gameFont)
:	renderWindow(window), font(gameFont),
	gameOver(false),
	launchBall(false), ballLaunchTimer(0), ballsLeft(gameConstants::BALLS_EXTRA_AVAILABLE), win(false),
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
	std::vector<Collision*>::iterator obj;

	for(obj = gameObjects.begin(); obj != gameObjects.end(); obj++)
	{
		delete *obj;
		*obj = nullptr;
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

	//prep for launching ball
	//create dummy ball
	ball = new Ball(gameConstants::BALL_DIAMETER, PolarVector(0, 0), Position(gameConstants::BALL_STARTING_X, gameConstants::BALL_STARTING_Y));
	// ball = new Ball(2, PolarVector(20, 90), Position(10, 10));
	gameObjects.push_back(ball);
	launchBall = true;
	ballLaunchTimer = 0;


	//initialize score text
	//lots of magic numbers to make it the correct size and location
	Size scoreSize(0, 2.5);
	Position scorePos(gameConstants::MAX_X - 20, gameConstants::MAX_Y - 1);
	scoreText.setFont(font);
	scoreText.setCharacterSize(scoreSize.transformToScreen().y);
	scoreText.setPosition(scorePos.transformToScreen());
	
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


		//check if player missed the ball
		if(ball->getPosition().y + ball->getHitbox().height/4 < 0 && !launchBall)
		{
			ballsLeft--;

			if(ballsLeft < 0)
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
	//display game objects
	for(Collision* object : gameObjects)
	{
		renderWindow.draw(*object->draw());

		if(GAMEPLAY_DEBUG)
		{
			renderWindow.draw(drawHitbox(object));
		}
	}


	//display on screen elements
	//balls left
	const Size onScreenBall(2, 2);
	sf::CircleShape circle(onScreenBall.transformToScreen().x/2);

	for(int i = 0; i < ballsLeft; i++)
	{
		renderWindow.draw(circle);
		circle.move(circle.getRadius()*2 + 3, 0);
	}

	//display text
	std::string scoreString = "SCORE: ";
	//TODO maybe just use raw score value instead of the one combined with the balls
	scoreString += std::to_string(getScore());
	scoreText.setString(scoreString);
	renderWindow.draw(scoreText);
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
	int score = Block::score;
	//player gets extra points if they didn't lose a ball
	score += 12 * ballsLeft;

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
		Block* middleBlock = nullptr;
		Block* prevBlock = nullptr;

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
			newBlock->setColor(gameConstants::BLOCK_COLORS[y]);

			//special game mechanic
			//if a block is larger than it's 2 neighbors, it will be white
			//and will have a larger speed increase
			if(prevBlock != nullptr && middleBlock != nullptr
				&& prevBlock->getHitbox() < middleBlock->getHitbox()
				&& middleBlock->getHitbox() > newBlock->getHitbox())
			{
				//change speed of the middle block
				middleBlock->setColor(sf::Color::White);
				middleBlock->setSpeed(currentSpeed + gameConstants::BLOCK_BALL_SPEED_INCREASE);
			}


			//add block to the main vector
			gameObjects.push_back(newBlock);

			//update variables
			usedWidth += width;
			prevBlock = middleBlock;
			middleBlock = newBlock;
		}

		//create the last block with the remaining width
		double width = gameConstants::MAX_X - usedWidth;
		Position blockPos(usedWidth + width/2, currentHeight);
		Size blockSize(width, gameConstants::BLOCKS_HEIGHT);
		Block* newBlock = new Block(blockPos, blockSize, currentSpeed);
		newBlock->setColor(gameConstants::BLOCK_COLORS[y]);
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



