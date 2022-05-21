#ifndef TEXTLIST_H
#define TEXTLIST_H

#include "../Common.h"
#include "../Physics.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>


/***************************************************************************************************
* TextList
*
* takes in an array of strings and prints them out in a vertical list
* with the first element being at the top and printing out going down
***************************************************************************************************/


class TextList
{
	public:
		TextList(sf::RenderWindow& window, sf::Font& textFont);
		
		//setters
		void setText(std::string textArr[], const int size);
		void sizeAndPosition(Size textHeight, Position topPos);
		void setCentered(bool isCentered);
		void setVerticalSpace(double space); //space between rows of text

		void display();


	private:
		//sfml stuff
		sf::RenderWindow& renderWindow;
		sf::Font& font;

		//for displaying text
		sf::Text _text;

		//user inputed stuff
		Size _textHeight;
		Position _pos;

		std::string* _textArr;
		int _arrSize;
		bool _centered;
		double _verticalSpace;
};


#endif
