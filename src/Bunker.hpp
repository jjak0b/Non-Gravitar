#pragma once

#include "Projectile.hpp"
#include "DamageableEntity.hpp"
#include "GameEngine.hpp"
#include "BunkerAShape.hpp"

class Bunker : public DamageableEntity{
	protected:
	double h = 300;
	int counter = 0;

	
	
	
	public:
		Bunker( Level *world, Point2D origin, double health, const char classname[]);

		bool Update(GameEngine* game);

		Projectile *Shoot(Point2D projectile_origin, Vector direction );

		int random(int range);


	
};