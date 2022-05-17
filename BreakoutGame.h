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
		void createBlockArray();
};


#endif
