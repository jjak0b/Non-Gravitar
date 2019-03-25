#pragma once

#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include "Viewport.hpp"
#include "Level.hpp"
#include <stddef.h>

class Entity{
protected:
	Level *world;
	Point2D origin;
	ColoredBitmap texture;
	char *str_classname;
public:
	Entity( Level *world, Point2D origin, ColoredBitmap *texture = NULL, char classname[] = "\0" );
	Point2D SetOrigin( Point2D origin );
	Point2D GetOrigin();
	void Draw( ViewPort *view );
	void Update();
	void Delete();
	void Callback_OnHit( Point2D hitOrigin, Entity *attacker );

};