#include "Menu.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>

#include "../game/Physics.h"
#include "../game/Block.h"
#include "ScoreBoard.h"


Menu::Menu(sf::RenderWindow& renderWindow, sf::Font& textFont)
:	renderWindow(renderWindow), font(textFont),
	scoreboard(renderWindow, font, MenuConstants::SCORE_FILE_PATH),
	menuText(new sf::Text[MENU_SIZE]),
	currentSelection(0), selectionMade(false), escaped(false),
	game(nullptr)
{
	//set up text font
	for(int i = 0; i < MENU_SIZE; i++)
	{
		menuText[i].setFont(font);
	}

	//setup scores
	try
	{
		scoreboard.readFile();
	}

	catch(ScoreBoard::FileError& error)
	{
		std::cout << "Could not find/open score file, creating one" << std::endl;
		//create blank score file
		std::fstream newFile;
		newFile.open(MenuConstants::SCORE_FILE_PATH, std::ios::out);

		if(newFile.is_open())
		{
			std::cout << "Successfully created score file" << std::endl;
		}

		else  
		{
			std::cout << "[ERROR] could not create a new scorefile" << std::endl;
			throw error;
		}

		newFile.close();
		//try to read newly created file
		//if this fails, just let an exception be thrown, there are other problems
		scoreboard.readFile();
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


void Menu::escape()
{
	escaped = true;
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

	escaped = false;
	gameClock.restart();
}


void Menu::exit()
{
	if(INTERFACE_DEBUG)
	{
		std::cout << "deleting game before exit" << std::endl;
	}

	//delete game upon exit to prevent memory leak
	delete game;
	game = nullptr;
}


//***************************************************************************************************
//private methods
//***************************************************************************************************

void Menu::playSetup()
{
	Block::score = 0;
	game = new BreakoutGame(renderWindow, font);
	game->setup();
}


bool Menu::play()
{
	game->run(gameClock);
	game->display();

	//if the player won/lost
	if(game->isGameOver())
	{
		//go to the scores screen
		currentSelection = 1;
		//add current score to the file
		scoreboard.addScore(game->getScore());

		//exit game
		delete game;
		game = nullptr;
		return true;
	}

	//just exit
	else if(escaped)
	{
		delete game;
		game = nullptr;
		return false;
	}

	else  
	{
		return true;
	}
}


bool Menu::scores()
{
	scoreboard.display();

	return !escaped;
}


bool Menu::credits()
{
	return false;
}

