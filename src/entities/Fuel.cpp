#include "Player.hpp"
#include "Level.hpp"
#include "engine/Bitmap.hpp"
#include "engine/GameEngine.hpp"
#include "engine/GameConfig.h"
#include "shared/Point2D.hpp"
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

