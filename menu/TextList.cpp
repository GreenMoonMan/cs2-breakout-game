#include "TextList.h"

TextList::TextList(sf::RenderWindow& window, sf::Font& textFont)
:	renderWindow(window), font(textFont),
	_textArr(nullptr), _arrSize(0),
	_centered(false), _verticalSpace(0)
{
	_text.setFont(textFont);
}


//setters
void TextList::setText(std::string textArr[], const int size)
{
	_textArr = textArr;
	_arrSize = size;
}


void TextList::sizeAndPosition(Size textHeight, Position topPos)
{
	_textHeight = textHeight;
	_pos = topPos;
}


void TextList::setCentered(bool isCentered)
{
	_centered = isCentered;
}


void TextList::setVerticalSpace(double space)
{
	_verticalSpace = space;
}


//---------------------------------------------------------------------------------------------------


void TextList::display()
{
	Position currentPos = _pos;

	_text.setCharacterSize(_textHeight.transformToScreen().y);


	for(int i = 0; i < _arrSize; i++)
	{
		//set correct text
		_text.setString(_textArr[i]);

		//center text if necessary
		if(_centered)
		{
			_text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2);
		}

		//set position
		_text.setPosition(currentPos.transformToScreen());

		//move position down for the next iteration
		currentPos.y -= _textHeight.height + _verticalSpace;

		//draw to screen
		renderWindow.draw(_text);
	}
}




