#pragma once

#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include "Viewport.hpp"
#include <stddef.h> // usato per definizione di NULL
class Level;
class GameEngine;

class Entity{
protected:
	Level *world;
	Point2D origin;
	ColoredBitmap texture;
	char *str_classname;
public:
	Entity( Level *world, Point2D origin, ColoredBitmap *texture = NULL, const char classname[] = "" );
	Point2D SetOrigin( Point2D origin );
	Point2D GetOrigin();
	void Draw( ViewPort *view );
	void Update( GameEngine *game );
	void Delete();
	void Callback_OnHit( Point2D hitOrigin, Entity *attacker );

};