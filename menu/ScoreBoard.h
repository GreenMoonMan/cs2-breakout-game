#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Common.h"
#include <fstream>


class ScoreBoard
{
	public:
		ScoreBoard(std::string filePath);
		~ScoreBoard();

		void readFile();
		void display();
		void addScore(int score);

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
		//dynamic array of scores
		std::string _filePath;
		int* _scoreArray;
		int _numOfScores;

		//private methods
		//finds out how many scores there are in the file
		int countNumberOfScores(std::fstream& file);
		void readIntoArray(std::fstream& file);
		void sortArray();
		bool searchForScore(int score);
};

#endif
