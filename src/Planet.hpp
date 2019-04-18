#pragma once

#include "Entity.hpp"
#include "Point2D.hpp"
#include <stddef.h>

class GameEngine;
class SolarSystem;
class Player;
class ViewPort;

class Planet : public Entity{
	private:
	unsigned int circumference;
	Level *subWorld = NULL; // il mondo appartente a questo pianeta
	// Nota: Entity.world è considerato il livello a cui questo pianeta appartiene: this->subWorld € this € this->world
	Player *player = NULL;

	public:
	Planet( SolarSystem *_solarSystem = NULL, Point2D _origin = Point2D( 0, 0 ), unsigned int _circumference = 100 );
	Level *GetSubWorld();
	Player *GetPlayer();
	bool Update( GameEngine *game );
	void Draw( ViewPort *view );
	void Delete();
	bool IsColliding( Entity *entity );
	void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
};