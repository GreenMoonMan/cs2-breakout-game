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
		template<typename T>
		int searchForType()
		{
			for(unsigned i = 0; i < gameObjects.size(); i++)
			{
				T* target = dynamic_cast<T*>(gameObjects.at(i));

				if(target != nullptr)
				{
					return i;
				}
			}

			return -1;
		}
};


#endif
