#pragma once

#include "Level.hpp"
#include "Planet.hpp"

class Player;

class SolarSystem : public Level{
	public:
	SolarSystem( unsigned int MaxWidth = 0, unsigned int MaxHeight = 0, unsigned int number_of_planets = 1, Player *_player = NULL );
};