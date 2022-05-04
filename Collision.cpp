#include "Collision.h"

//constructors
Collision::Collision(double x, double y, double width, double height)
: _pos(x, y), _width(width), _height(height)
{ }


Collision::Collision(double x, double y)
: Collision(x, y, 0, 0)
{ }


Collision::Collision()
: Collision(0, 0, 0, 0)
{ }



//getters
double Collision::getX() const
{
	return _pos.x;
}


double Collision::getY() const
{
	return _pos.y;
}


double Collision::getHbWidth() const
{
	return _width;
}


double Collision::getHbHeight() const
{
	return _height;
}
