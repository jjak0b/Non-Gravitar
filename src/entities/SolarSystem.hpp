#pragma once

#include "Level.hpp"

class SolarSystem : public Level{
	public:
    unsigned int count_planets;

	SolarSystem( Vector bounds, unsigned int number_of_planets = 1 );

	virtual bool Update( GameEngine *game );

    virtual void Generate( GameEngine *game );

	virtual bool IsGenerated();
};