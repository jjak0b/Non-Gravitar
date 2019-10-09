#pragma once

#include "DynamicEntity.hpp"
class Damageable;

class Beam : public Entity{
	protected:
	Beam *next = NULL;
	bool death = false;
	bool add = false;


	public:
	Beam( Level *world, Point2D origin );




	void Kill(GameEngine *game);
	void addNext();
};