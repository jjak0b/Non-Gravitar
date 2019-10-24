#pragma once
#include "Entity.hpp"

#define DEFAULT_PLANET_ENTITY_COLOR COLOR_ORANGE

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
	/**
	 * @brief Direzione del sistema solare opposta alla quale il giocatore entra nel pianeta
	 */
	Vector escape_direction;

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
	PlanetEntity( SolarSystem *_world = NULL, Point2D origin = Point2D(0,0), Bitmap *texture = NULL, unsigned int _radius = 4, Vector _bounds = Vector( 2 ) );

	/**
	 * PreCondition: requisiti Entity::~Entity()
	 */
	virtual ~PlanetEntity();

	/**
	 * @brief Dealloca le risorse occupate da questa'entità ( Vedere anche Entity::Delete() )
	 * PostCondition: il giocatore nel livello di questo pianeta non viene deallocato
	 */
	virtual void Delete( GameEngine* game );
	
	PlanetLevel *GetPlanetLevel();

	void SetPlanetLevel( PlanetLevel *planet_world );

	virtual bool Update( GameEngine *game );

	virtual void Draw( ViewPort *view );

	virtual bool IsColliding( Entity *entity );

	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};