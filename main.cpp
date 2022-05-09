#include "Collision.h"
#include "Common.h"
#include "Physics.h"
#include "Paddle.h"

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

	renderWindow.setFramerateLimit(75);

	sf::Clock clock;

	Paddle pad(Size(20, 5));


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


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			pad.move(40);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			pad.move(-40);


		renderWindow.clear();

		pad.update(clock);
		clock.restart();
		sf::Drawable* toDraw = pad.draw();
		renderWindow.draw(*toDraw);

		renderWindow.display();
	}

	return 0;
}

