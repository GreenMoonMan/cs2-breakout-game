#include "Collision.h"
#include "Common.h"
#include "Physics.h"
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include "Block.h"
#include "BreakoutGame.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

using namespace std;



int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(gameConstants::SCREEN_WIDTH, gameConstants::SCREEN_HEIGHT), "wow! much game!", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	renderWindow.setFramerateLimit(75*2);
	// renderWindow.setVerticalSyncEnabled(true);

	sf::Clock clock;
	
	BreakoutGame game(renderWindow);
	game.setup();


	while(renderWindow.isOpen())
	{
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::EventType::Closed)
				renderWindow.close();
			
			if(event.type == sf::Event::EventType::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
					renderWindow.close();
			}
		}

		renderWindow.clear();
		static bool scoreFlag = false;

		if(!game.isGameOver())
		{
			game.run(clock);
		}

		else if(!scoreFlag)
		{
			cout << "score: " << game.getScore() << endl;
			scoreFlag = true;
		}


		game.display();

		clock.restart();
		renderWindow.display();
	}

	return 0;
}

