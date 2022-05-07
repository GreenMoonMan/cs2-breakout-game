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
	sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "wow! much game!", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	renderWindow.setFramerateLimit(75);

	sf::RectangleShape rect(sf::Vector2f(200, 200));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(3);
	rect.setPosition(500, 500);

	Collision col(80, 45, 20, 20);

	sf::RectangleShape hitbox = drawHitbox(col);
	cout << hitbox.getSize().x << "\t" << hitbox.getSize().y << endl;


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
		// renderWindow.draw(rect);
		renderWindow.draw(hitbox);
		renderWindow.display();
	}

	return 0;
}

