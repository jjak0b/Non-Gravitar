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
	/**
	 * @brief Raggio del pianeta dal punto di vista del sistema solare:
	 * ha solo funzione di controllo durante collisione e in fase di draw.
	 * Nota: Totalmente non legata a max_longitude (vedere documentazione)!!
	 */
	unsigned int radius;
	
	/**
	 * @brief Lunghezza della superficie dal punto di vista del pianeta; considerabile come anche la circonferenza del pianeta.
	 *	Dal punto di vista pratico radius e max_longitude hanno le stesse unità di misura,
	 *	però in realtà devono essere pensate come se avessero unità di misura diverse, poichè utilizzati in contesti diversi:
	 *	max_longitude è utilizzata per un subWorld di Planet, mentre radius è utilizzata in SolarSystem.
	 */
	unsigned int max_longitude;

	/**
	 * @brief Altitudine dal livello 0 della superficie del pianeta
	 * Nota: corrisponde all'altezza massima dentro la quale si è presenti nel pianeta
	 */
	unsigned int max_altitude;
	
	/**
	 * @brief il mondo appartente a questo pianeta
	 * Nota: Entity.world è considerato il livello a cui questo pianeta appartiene: this->subWorld € this € this->world
	 */
	Level *subWorld = NULL;
	Player *player = NULL;

	public:
	Planet( SolarSystem *_solarSystem = NULL, Point2D _origin = Point2D( 0, 0 ), unsigned int radius = 1, unsigned int longitude = 100, unsigned int altitude = 30 );
	SolarSystem *GetWorld();
	Level *GetSubWorld();
	Player *GetPlayer();
	bool Update( GameEngine *game );
	void Draw( ViewPort *view );
	void Delete();
	bool IsColliding( Entity *entity );
	void Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin );
};