#include "Menu.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <iterator>

#include "../game/Physics.h"
#include "../game/Block.h"


Menu::Menu(sf::RenderWindow& renderWindow, sf::Font& textFont)
:	renderWindow(renderWindow), font(textFont),
	menuText(new sf::Text[MENU_SIZE]),
	currentSelection(0), selectionMade(false)
{
	//set up text font
	for(int i = 0; i < MENU_SIZE; i++)
	{
		menuText[i].setFont(font);
	}
}


Menu::~Menu()
{
	//delete array
	delete[] menuText;
}

//***************************************************************************************************
//navigation
//***************************************************************************************************

void Menu::up()
{
	//prevent changing when seleciton has already been made and make sure current selection doesn't go out of bounds
	if(!selectionMade && currentSelection > 0)
	{
		currentSelection--;
	}
}


void Menu::down()
{
	//same thing as up
	if(!selectionMade && currentSelection < MENU_SIZE-1)
	{
		currentSelection++;
	}
}


void Menu::select()
{
	if(currentSelection == 0 && !selectionMade)
	{
		playSetup();
	}

	gameClock.restart();
	selectionMade = true;
}


//***************************************************************************************************
//
//***************************************************************************************************


void Menu::update()
{
	if(selectionMade)
	{
		//call appropriate functions
		//the function specifies wheter it is time to exit
		switch (currentSelection)
		{
			case 0:
				selectionMade = play();
				break;
			
			case 1:
				selectionMade = scores();
				break;
			
			case 2:
				selectionMade = credits();
		}
	}


	//display menu
	else
	{
		Size textHeight(0, 4);
		Position textPos(gameConstants::MAX_X / 2, gameConstants::MAX_Y - 40);

		//apply to each item in the menu
		for(int i = 0; i < MENU_SIZE; i++)
		{
			std::string menuString;

			menuText[i].setFillColor(sf::Color(20, 255, 90));

			//place cursor
			if(currentSelection == i)
			{
				menuString = ">";
				menuText[i].setStyle(sf::Text::Underlined);
			}

			else  
			{
				menuString = " ";
				menuText[i].setStyle(sf::Text::Regular);
			}

			//set correct text
			menuString += MENU_ITEMS[i];
			menuText[i].setString(menuString);

			//put into correct position
			//first set correct size
			menuText[i].setCharacterSize(textHeight.transformToScreen().y);
			//set origin to the center
			menuText[i].setOrigin(menuText[i].getLocalBounds().width/2, menuText[i].getLocalBounds().height/2);
			menuText[i].setPosition(textPos.transformToScreen());

			//move textPos down for next iteration
			textPos.y -= textHeight.height + 3;

			//draw to screen
			renderWindow.draw(menuText[i]);
		}
	}


	gameClock.restart();
}


//***************************************************************************************************
//private methods
//***************************************************************************************************

void Menu::playSetup()
{
	game = new BreakoutGame(renderWindow, font);
	Block::score = 0;
	game->setup();
}


bool Menu::play()
{
	game->run(gameClock);
	game->display();

	if(game->isGameOver())
	{
		// delete game;
		return false;
	}

	else  
	{
		return true;
	}
}


bool Menu::scores()
{
	return false;
}


bool Menu::credits()
{
	return false;
}

