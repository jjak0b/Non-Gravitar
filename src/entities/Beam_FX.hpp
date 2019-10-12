#pragma once
#include "Entity.hpp"

class Beam_FX : public Entity{
	protected:
	Beam_FX *next = NULL;

	public:
	Beam_FX( Level *world, Point2D origin );

	void addNext(Point2D origin);
	virtual void Delete( GameEngine* game );
};