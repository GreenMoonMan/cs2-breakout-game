#ifndef BREAKOUTGAME_H
#define BREAKOUTGAME_H

#include "Common.h"
#include "Collision.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>


class BreakoutGame
{
	public:
		BreakoutGame(sf::RenderWindow& window);
		~BreakoutGame();

		//the main game
		void setup();
		void run(const sf::Clock& clock);
		void display();

		//other methods
		bool isGameOver();
		int getScore();


	private:
		static const int NUM_OF_WALLS = 3;

		sf::RenderWindow& renderWindow;

		//game data
		int score;
		bool gameOver;

		//other attributes
		int ballsLeft = 3;
		bool launchBall;
		double ballLaunchTimer;

		//game objects
		//all game objects are stored in this polymorhpic vector
		std::vector<Collision*> gameObjects;
		Wall* walls[NUM_OF_WALLS];
		Paddle* paddle;
		Ball* ball;

		//private methods
		void createBlocks();

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
