#include "Collision.h"
#include "Common.h"
#include "Physics.h"
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include "Block.h"

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

	// renderWindow.setFramerateLimit(75*2);
	renderWindow.setVerticalSyncEnabled(true);

	sf::Clock clock;

	Paddle pad(Size(20, 1.5));
	Ball ball(4, 60, 60);
	Block block(Position(50, 50), Size(20, 10), 20);
	Wall walls[4] = {Wall(Wall::LEFT), Wall(Wall::RIGHT), Wall(Wall::TOP), Wall(Wall::BOTTOM)};


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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			pad.move(80);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			pad.move(-80);
		
		
		//check for wall collisions
		for(int i = 0; i < 4; i++)
		{
			if(checkCollision(&pad, &walls[i]))
			{
				pad.collisionAction(&walls[i]);
			}

			if(checkCollision(&ball, &walls[i]))
			{
				ball.collisionAction(&walls[i]);
			}
		}

		if(checkCollision(&ball, &pad))
		{
			ball.collisionAction(&pad);
		}

		//collison with the ball and block	
		if(checkCollision(&ball, &block))
		{
			ball.collisionAction(&block);
			block.collisionAction(&ball);
		}



		pad.update(clock);
		ball.update(clock);

		sf::Drawable* toDraw = pad.draw();
		renderWindow.draw(*toDraw);
		renderWindow.draw(*ball.draw());
		renderWindow.draw(*block.draw());
		renderWindow.draw(drawHitbox(&pad));
		renderWindow.draw(drawHitbox(&ball));
		renderWindow.draw(drawHitbox(&block));

		for(int i = 0; i < 4; i++)
		{
			renderWindow.draw(drawHitbox(&walls[i]));
		}

		clock.restart();
		renderWindow.display();
	}

	return 0;
}

