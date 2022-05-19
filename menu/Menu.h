#ifndef MENU_H
#define MENU_H

#include "../Common.h"
#include "../game/BreakoutGame.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>


class Menu
{
	public:
		Menu(sf::RenderWindow& window, sf::Font& textFont);
		~Menu();
	
		//movement
		void up();
		void down();
		void select();

		void update();


	private:
		static const int MENU_SIZE = 3;
		const std::string MENU_ITEMS[MENU_SIZE] = 
			{
				"PLAY", "SCORES", "CREDITS"
			};
		
		//sfml stuff
		sf::RenderWindow& renderWindow;
		sf::Font& font;

		//dynamic array of selectable text
		sf::Text* menuText;

		int currentSelection;
		bool selectionMade;

		//for game
		BreakoutGame* game;
		sf::Clock gameClock;

		//private methods
		void showMenu(int position);

		//returns false when exited
		void playSetup();
		bool play();
		void scoresSetup();
		bool scores();
		void creditsSetup();
		bool credits();
};

#endif