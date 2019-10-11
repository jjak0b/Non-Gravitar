#pragma once

#include "Entity.hpp"

class Damageable;

class Beam : public Entity{
	protected:
	Beam *next = NULL;

	public:
	Beam( Level *world, Point2D origin );

	virtual void Delete( GameEngine* game );
	void addNext(Point2D origin);
};