#pragma once

#include "DamageableEntity.hpp"
#include "Level.hpp"

class Player : public DamageableEntity{
	public:
	Player( Level *world, Point2D origin, double health );
	void Update( GameEngine *game );
	bool shoot(GameEngine *game);
	bool beam(GameEngine *game);
};
