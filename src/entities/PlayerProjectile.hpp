#pragma once
#include "Projectile.hpp"

class PlayerProjectile : public Projectile {


	public:
	PlayerProjectile( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed, double damage );
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};