#pragma once

#include "Level.hpp"

class SolarSystem : public Level{
	public:
	SolarSystem( unsigned int MaxWidth = 0, unsigned int MaxHeight = 0, unsigned int number_of_planets = 1 );

	virtual bool Update( GameEngine *game );
	virtual bool IsGenerated();
};