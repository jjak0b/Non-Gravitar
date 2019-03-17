#pragma once

#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include "Viewport.hpp"

class Entity{
protected:
	Point2D origin;
	ColoredBitmap texture;
	char *str_classname;
public:
	Entity( unsigned int x, unsigned int y, char classname[] = "\0" );
	Point2D SetOrigin( unsigned int x, unsigned int y );
	Point2D GetOrigin();
	void Draw( ViewPort *view );
	void Update();
	void Delete();
};