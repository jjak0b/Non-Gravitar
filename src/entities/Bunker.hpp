#pragma once

#include "Entity.hpp"
#include "Damageable.hpp"

class Projectile;

class Bunker : public Entity, public Damageable {
	protected:
	double timer = 0;

	public:
		Bunker( Level *world, Point2D origin, double health, const char classname[] );

		virtual bool Update(GameEngine* game);

		virtual void Draw(ViewPort* view);

		Projectile *Shoot(Point2D projectile_origin, Vector direction );

		int random(int range);


	
};