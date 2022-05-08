#include "Collision.h"
#include "Common.h"
#include "Physics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
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

	Collision col1(0, 11, 30, 20);
	Collision col2(50, 40, 10, 30);
	sf::RectangleShape hitbox1;
	sf::RectangleShape hitbox2;


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


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			col1._pos.x += 0.5;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			col1._pos.x -= 0.5;
			
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			col1._pos.y += 0.5;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			col1._pos.y -= 0.5;

		hitbox1 = drawHitbox(col1);
		hitbox2 = drawHitbox(col2);
		
		if(checkCollision(&col1, &col2))
		{
			hitbox1.setOutlineColor(sf::Color::Blue);
			hitbox2.setOutlineColor(sf::Color::Blue);
		}

		renderWindow.clear();
		renderWindow.draw(hitbox1);
		renderWindow.draw(hitbox2);
		renderWindow.display();
	}

	return 0;
}

