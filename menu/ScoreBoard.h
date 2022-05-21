#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Common.h"
#include "TextList.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>


/***************************************************************************************************
* ScoreBoard
*
* displays high scores from a score file and can also write new scores to the score file
*
* readFile() will throw a file exception if the score file could not be opened
* most likely this is because it does not exist
***************************************************************************************************/


class ScoreBoard
{
	public:
		ScoreBoard(sf::RenderWindow& window, sf::Font& font, std::string filePath);
		~ScoreBoard();

		void readFile();
		//adds score to the score file if it is unique
		void addScore(int score);
		//draws scores to the screen
		void display();

		//error class
		class FileError
		{
			public:
				FileError(std::string e);
				std::string what();

			private:
				std::string _e;
		};


	private:
		//for drawing scores
		sf::RenderWindow& renderWindow;
		TextList _scoreList;

		sf::Text _headerText;

		//dynamic array of scores
		std::string _filePath;
		int* _scoreArray;
		//_scoreStrings is the array that actually gets displayed
		//it will contain at most 10 scores
		std::string* _scoreStrings;
		int _numOfScores;
		//how many scores are in _scoreStrings
		int _numOfScoresOnScreen;

		//private methods
		//finds out how many scores there are in the file
		int countNumberOfScores(std::fstream& file);
		void readIntoArray(std::fstream& file);
		void sortArray();
		bool searchForScore(int score);
		//puts the highest scores into _scoreStrings to be displayed
		void updateScoreStrings();
};

#endif
