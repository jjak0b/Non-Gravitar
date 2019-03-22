#pragma once

#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include "Viewport.hpp"

class Entity{
protected:
	Level *world;
	Point2D origin;
	ColoredBitmap texture;
	char *str_classname;
public:
	Entity( Level *world, Point2D origin, ColoredBitmap *texture, char classname[] = "\0" );
	Point2D SetOrigin( Point2D origin );
	Point2D GetOrigin();
	void Draw( ViewPort *view );
	void Update();
	void Delete();
};