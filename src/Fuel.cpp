#include "Player.hpp"
#include "Level.hpp"
#include "Bitmap.hpp"
#include "GameEngine.hpp"
#include "GameConfig.h"
#include "Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include "Fuel.hpp"

Fuel::Fuel( Level *world, Point2D origin) : Entity( world, origin, NULL, "Fuel" ){
}

bool Fuel::Update(GameEngine *game) {
	return this->Entity::Update( game );
}

