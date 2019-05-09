#pragma once
#include "Entity.hpp"
#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include <stddef.h>

class SolarSystem;
class PlanetLevel;

class PlanetEntity : public Entity{
	public:
	unsigned int radius;

	protected:
	PlanetLevel *planet_level;

	public:
	PlanetEntity( SolarSystem *_world = NULL, Point2D origin = Point2D(0,0), ColoredBitmap *texture = NULL, unsigned int _radius = 4, unsigned int max_longitude = 100, unsigned int max_altitude = 30 );

	PlanetLevel *GetPlanetLevel();

	bool Update( GameEngine *game );

	void Draw( ViewPort *view );

	bool IsColliding( Entity *entity );

	void Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin );

	/**
	 * @brief Dealloca le risorse occupate da questa'entità ( Vedere anche Entity::Delete() )
	 * PostCondition: il giocatore nel livello di questo pianeta non viene deallocato
	 */
	void Delete();
};