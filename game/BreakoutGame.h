#ifndef BREAKOUTGAME_H
#define BREAKOUTGAME_H

#include "../Common.h"

#include "Collision.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "Block.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>


/***************************************************************************************************
* BreakoutGame
*
* this is the main breakout game
* constructor takes the main window and which font to use
* 
* setup() is called only once to setup the game, must be called before run() can be called
*
* run(clock) must be called in a loop, clock must be reset each loop, as it keeps track of the change in time
* this method handle physics, user input, etc...
*
* display(): draws everything to the screen, also must be called in a loop
*
* the game is finished when the isGameOver() returns true
*
* a Breakout game object can only be used once per game
* it should be created right before use and deleted right after
***************************************************************************************************/


class BreakoutGame
{
	public:
		BreakoutGame(sf::RenderWindow& window, sf::Font& gameFont);
		~BreakoutGame();

		//the main game
		void setup();
		void run(const sf::Clock& clock);
		void display();

		//other methods
		//if the player lost all balls or won
		bool isGameOver();
		//if all the blocks have been destroyed
		bool isGameWon();
		//score of the blocks destroyed + bonus score from additional non-lost balls
		int getScore();


	private:
		static const int NUM_OF_WALLS = 3;

		//sfml stuff
		sf::RenderWindow& renderWindow;
		sf::Font& font;

		//game data
		bool gameOver;
		sf::Text scoreText;

		//other attributes
		bool launchBall;
		double ballLaunchTimer;
		int ballsLeft;
		bool win;

		//game objects
		//all game objects are stored in this polymorhpic vector
		std::vector<Collision*> gameObjects;
		Wall* walls[NUM_OF_WALLS];
		Paddle* paddle;
		Ball* ball;


		//--------------------------------------------------
		//private methods
		void createBlocks();
		void launchNewBall();

		//searches for the first instance of an object in gameObjects
		//returns the index of the found element, or -1 if the search failed
		//uses a linear search
		template<typename T>
		int searchForType(unsigned startingIndex = 0)
		{
			//base condition
			//reached the end of the array
			if(startingIndex == gameObjects.size())
			{
				return -1;
			}

			//check if dynamic cast works
			T* target = dynamic_cast<T*>(gameObjects.at(startingIndex));

			if(target != nullptr)
			{
				return startingIndex;
			}

			//recursive case
			return searchForType<T>(startingIndex + 1);
		}
};


#endif
