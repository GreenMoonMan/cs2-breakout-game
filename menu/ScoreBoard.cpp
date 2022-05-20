#include "ScoreBoard.h"
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <ios>
#include <string>


using namespace std;


ScoreBoard::ScoreBoard(sf::RenderWindow& window, sf::Font& font, std::string filePath)
:	renderWindow(window), _scoreList(window, font),
	_filePath(filePath),
	_scoreArray(nullptr), _numOfScores(0)
{
	//for displaying the header
	_headerText.setString("TOP SCORES:");

	_headerText.setFont(font);
	Position headerPos(gameConstants::MAX_X/2, gameConstants::MAX_Y - 5);
	Size headerHeight(0, 5);
	_headerText.setCharacterSize(headerHeight.transformToScreen().y);
	
	//set origin to center and position correctly
	_headerText.setOrigin(_headerText.getLocalBounds().width/2, _headerText.getLocalBounds().height/2);
	_headerText.setPosition(headerPos.transformToScreen());
}


ScoreBoard::~ScoreBoard()
{
	delete[] _scoreArray;
}



void ScoreBoard::readFile()
{
	std::fstream scoreFile;
	scoreFile.open(_filePath, std::ios::in);

	if(scoreFile.is_open())
	{
		//read file into array
		_numOfScores = countNumberOfScores(scoreFile);

		//create array for scores
		_scoreArray = new int[_numOfScores];
		readIntoArray(scoreFile);
		scoreFile.close();

		sortArray();

		if(INTERFACE_DEBUG)
		{
			cout << "number of scores: " << _numOfScores << "\n";
			cout << "scores: \n";
			
			for(int i = 0; i < _numOfScores; i++)
			{
				cout << _scoreArray[i] << "\n";
			}

			cout << endl;
		}
	}

	//if the file failed to open
	else
	{
		throw FileError("Failed to open score file");
	}
}


//---------------------------------------------------------------------------------------------------

void ScoreBoard::addScore(int score)
{
	std::fstream scoreFile;
	scoreFile.open(_filePath, std::ios::app);

	if(scoreFile.is_open())
	{
		//add score only if it is not alread in the file
		//if the score is already in the file, there is no need to add it
		if(!searchForScore(score))
		{
			//write new score to file
			scoreFile << score << endl;

			//update array with new score
			//create new larger array
			int* newScores = new int[_numOfScores+1];

			//assign scores to new array
			for(int i = 0; i < _numOfScores; i++)
			{
				newScores[i] = _scoreArray[i];
			}

			newScores[_numOfScores] = score;

			//delete old array and replace with new one
			delete[] _scoreArray;
			_scoreArray = newScores;
			_numOfScores++;

			sortArray();

			//debug
			if(INTERFACE_DEBUG)
			{
				cout << "added score, new scores: \n";

				for(int i = 0; i < _numOfScores; i++)
				{
					cout << _scoreArray[i] << "\n";
				}

				cout << endl;
			}
		}

		scoreFile.close();
	}

	//if the file failed to open
	else
	{
		throw FileError("Failed to open score file");
	}
}


//---------------------------------------------------------------------------------------------------

void ScoreBoard::display()
{
	//TODO fix this attrocity
	//also make max of 20 or so scores to display
	string* scoreText = new string[_numOfScores];
	
	for(int i = 0; i < _numOfScores; i++)
	{
		//add a rank number first
		scoreText[i] = to_string(i + 1) + ":  ";
		scoreText[i] += to_string(_scoreArray[i]);
	}

	//more magic numbers to set position correctly
	_scoreList.setText(scoreText, _numOfScores);
	_scoreList.sizeAndPosition(Size(0, 3), Position(gameConstants::MAX_X/2 - 5, gameConstants::MAX_Y - 20));
	_scoreList.setVerticalSpace(3);
	_scoreList.display();

	delete[] scoreText;

	//display header
	renderWindow.draw(_headerText);
}



//***************************************************************************************************
//private methods
//***************************************************************************************************

int ScoreBoard::countNumberOfScores(std::fstream& file)
{
	std::string line;
	int scores = 0;

	//read through file counting the number of scores
	while(std::getline(file, line))
	{
		if(!line.empty())
		{
			scores++;
		}
	}

	//reset file to the beginning
	file.clear();
	file.seekg(0, std::ios::beg);

	return scores;
}


void ScoreBoard::readIntoArray(std::fstream& file)
{
	string line;
	int scoreIndex = 0;

	while(getline(file, line))
	{
		//read score into array if it isn't empty
		if(!line.empty())
		{
			//put score into array
			_scoreArray[scoreIndex] = stoi(line);

			//this should never be thrown, placed for debug purposes
			if(scoreIndex >= _numOfScores)
			{
				throw FileError("Scores were read incorrectly, too many to fit in array");
			}

			scoreIndex++;
		}
	}

	//reset file to the beginning
	file.clear();
	file.seekg(0, std::ios::beg);
}


void ScoreBoard::sortArray()
{
	//bubble sort on array
	for(int end = _numOfScores - 1; end > 0; end--)
	{
		for(int i = 0; i < end; i++)
		{
			//sort from highest to lowest
			if(_scoreArray[i] < _scoreArray[i+1])
			{
				//swap elements
				int temp = _scoreArray[i];
				_scoreArray[i] = _scoreArray[i+1];
				_scoreArray[i+1] = temp;
			}
		}
	}
}


bool ScoreBoard::searchForScore(int score)
{
	//TODO maybe convert to binary search since it is sorted
	for(int i = 0; i < _numOfScores; i++)
	{
		if(_scoreArray[i] == score)
		{
			return true;
		}
	}

	return false;
}


//***************************************************************************************************
//FileError
//***************************************************************************************************

ScoreBoard::FileError::FileError(std::string e)
:	_e(e)
{ }


std::string ScoreBoard::FileError::what()
{
	return _e;
}



