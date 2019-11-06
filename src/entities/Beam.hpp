#pragma once

#include "Projectile.hpp"
#include "Beam_FX.hpp"

class Beam : public Projectile{
	protected:
	Beam_FX *fx;	// Texture del raggio.
	public:
	Beam( Level *world, Point2D origin, Vector direction);
	virtual bool Update( GameEngine *game );
};