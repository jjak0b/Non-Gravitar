#pragma once

#include "Entity.hpp"
#include "Level.hpp"

class Player : public Entity{
	
	Player( Level *world, Point2D origin );
};
