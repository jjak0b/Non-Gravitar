#pragma once

#include "Entity.hpp"

class Fuel : public Entity{
	protected:
	double size;

	public:
	Fuel( Level *world, Point2D origin );

	bool Update(GameEngine *game);


};