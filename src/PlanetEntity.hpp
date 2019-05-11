#pragma once
#include "Entity.hpp"
#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include <stddef.h>

class SolarSystem;
class PlanetLevel;

class PlanetEntity : public Entity{
	public:

	/**
	 * @brief Raggio del pianeta dalla vista del giocatore;
	 * Non è legato in alcun modo con gli attributi di planet_level, poichè è utilizzato
	 * per disegnare il pianeta nella viewport (dal systema solare),
	 * e per tracciare quando avviene la collisione con il giocatore
	 */
	unsigned int radius;

	/**
	 * @brief Punto del sistema solare che è definito intorno a questa entità:
	 * Esso viene ridefinito ogni volta che il giocatore entra nel pianeta, e
	 * verrà considerato come punto "sicuro" dove riapparirà nel sistema solare dopo essere usciti dal pianeta.
	 */
	Point2D escape_point;

	protected:

	/**
	 * @brief Livello associato a questo pianeta:
	 * Quando Viene richiamata Callback_OnCollide, il frame successivo verranno aggiornati e visualizzati
	 * gli elementi di questo livello.
	 * Quando il giocatore esce dal livello, il frame successivo verranno aggiornati e visualizzati
	 * gli elementi del mondo in cui risiede questo PlanetEntity
	 */
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