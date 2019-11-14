#pragma once
#include "Projectile.hpp"

class PlayerProjectile : public Projectile {


	public:
	PlayerProjectile( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed );
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};