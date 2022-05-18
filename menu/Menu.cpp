#include "Menu.h"
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <iterator>
#include "../game/Physics.h"


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
		std::cout << "enter!!!" << std::endl;
		selectionMade = false;
	}


	//display menu
	else
	{
		Size textHeight(0, 6);
		Position textPos(gameConstants::MAX_X / 2, gameConstants::MAX_Y - 20);

		//apply to each item in the menu
		for(int i = 0; i < MENU_SIZE; i++)
		{
			std::string menuString;

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
}


//***************************************************************************************************
//private methods
//***************************************************************************************************

void Menu::play()
{

}


void Menu::scores()
{

}


void Menu::credits()
{

}

