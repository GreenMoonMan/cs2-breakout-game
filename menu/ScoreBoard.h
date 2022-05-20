#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Common.h"
#include "TextList.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>


class ScoreBoard
{
	public:
		ScoreBoard(sf::RenderWindow& window, sf::Font& font, std::string filePath);
		~ScoreBoard();

		void readFile();
		void addScore(int score);
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
		std::string* _scoreStrings;
		int _numOfScores;
		int _numOfScoresOnScreen;

		//private methods
		//finds out how many scores there are in the file
		int countNumberOfScores(std::fstream& file);
		void readIntoArray(std::fstream& file);
		void sortArray();
		bool searchForScore(int score);
		void updateScoreStrings();
};

#endif
