#include "Common.h"
#include "Physics.h"

#include "game/Collision.h"
#include "game/Paddle.h"
#include "game/Wall.h"
#include "game/Ball.h"
#include "game/Block.h"
#include "game/BreakoutGame.h"

#include "menu/Menu.h"
#include "menu/ScoreBoard.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <cstddef>
#include <cstdlib>

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

	renderWindow.setFramerateLimit(75*3);
	// renderWindow.setVerticalSyncEnabled(true);

	srand(time(0));

	sf::Clock clock;

	sf::Font font;
	// font.loadFromFile("assets/Connection2.otf");

	if(!font.loadFromFile(MenuConstants::FONT_FILE_PATH))
	{
		//if font failed to load
		cout << "[ERROR] could not find font \"" << MenuConstants::FONT_FILE_PATH << "\"\n"
			<<"hint: was the game run from the \"bin/\" directory?" << endl;

		return 1;
	}

	Menu mainMenu(renderWindow, font);


	while(renderWindow.isOpen())
	{
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::EventType::Closed)
			{
				mainMenu.exit();
				renderWindow.close();
			}
			
			if(event.type == sf::Event::EventType::KeyPressed)
			{
				//if ctrl+q was pressed
				if(event.key.code == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					mainMenu.exit();
					renderWindow.close();
				}
				
				if(event.key.code == sf::Keyboard::Escape)
					mainMenu.escape();

				if(event.key.code == sf::Keyboard::Up)
					mainMenu.up();

				if(event.key.code == sf::Keyboard::Down)
					mainMenu.down();

				if(event.key.code == sf::Keyboard::Enter)
					mainMenu.select();
			}
		}

		renderWindow.clear();
		
		mainMenu.update();

		clock.restart();
		renderWindow.display();
	}

	return 0;
}

