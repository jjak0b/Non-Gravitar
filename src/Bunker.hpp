#pragma once

#include "DamageableEntity.hpp"
#include "Projectile.hpp"

class Bunker : public DamageableEntity{
	protected:
	int counter = 0;

	public:
		Bunker( Level *world, Point2D origin, double health, const char classname[] );

		virtual bool Update(GameEngine* game);

		Projectile *Shoot(Point2D projectile_origin, Vector direction );

		int random(int range);


	
};