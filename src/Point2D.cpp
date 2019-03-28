#include "Point2D.hpp"

Point2D::Point2D( int _x, int _y ){
	this->x = _x;
	this->y = _y;
}

bool Point2D::Equals( Point2D p ){
	return p.x == this->x && p.y == this->y;
}