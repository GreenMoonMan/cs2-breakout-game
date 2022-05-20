#ifndef WALL_H
#define WALL_H

#include "../Physics.h"
#include "Collision.h"
#include <SFML/Graphics/RectangleShape.hpp>


class Wall : public Collision
{
	public:
		enum Side {LEFT, RIGHT, TOP, BOTTOM};
		Wall(Side location);
		virtual ~Wall();

		Side getSide() const;

		virtual void collisionAction(Collision*);
		virtual sf::Drawable* draw();

	private:
		Side _location;
		sf::RectangleShape* _dummyRect;
};


#endif
