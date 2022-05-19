#ifndef TEXTLIST_H
#define TEXTLIST_H

#include "../Common.h"
#include "../game/Physics.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>


class TextList
{
	public:
		TextList(sf::RenderWindow& window, sf::Font& textFont);
		
		//setters
		void setText(std::string textArr[], const int size);
		void sizeAndPosition(Size textHeight, Position topPos);
		void setCentered(bool isCentered);
		void setVerticalSpace(double space);

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
