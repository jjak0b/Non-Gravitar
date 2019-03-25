#pragma once

#include "DamageableEntity.hpp"
#include "Level.hpp"

class Player : public DamageableEntity{
	public:
	Player( Level *world, Point2D origin, double health );
};
