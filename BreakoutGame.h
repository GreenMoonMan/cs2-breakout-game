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
		BreakoutGame(sf::RenderWindow&);
		~BreakoutGame();

		//the main game
		void setup();
		void run(const sf::Clock& clock);
		void display();

		//other methods
		bool isGameOver();
		bool getScore();


	private:
		sf::RenderWindow& renderWindow;

		//game objects
		//all game objects are stored in this vector
		std::vector<Collision*> gameObjects;
		Ball* ball;
		Paddle* paddle;
		const int NUM_OF_WALLS = 3;
		Wall** walls;

		//game data
		int score;
		bool gameOver;
};


#endif
