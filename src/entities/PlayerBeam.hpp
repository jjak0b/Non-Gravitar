#pragma once

#include "Projectile.hpp"
#include "Beam_FX.hpp"

class PlayerBeam : public Projectile{
	protected:
	Beam_FX *fx;	// Texture del raggio.
	public:
	PlayerBeam( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed );
	virtual bool Update( GameEngine *game );
};