#pragma once

#include "Projectile.hpp"
#include "DamageableEntity.hpp"
#include "GameEngine.hpp"

class Bunker : public DamageableEntity{
	protected:
	double h = 300;
	int type = 1;
	int counter = 0;
	
	
	public:
		Bunker( Level *world, Point2D origin, int type);
		bool Update();
		Projectile *Fire( Vector direction );

	bool Update(GameEngine* game);

	Projectile *shoot( Vector direction );
	int random(int range);
	
};