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
	/**
	 * @brief Costruttore di un'entità pianeta di un certo raggio, con il suo livello pianeta associato aventi le dimensioni di bounds fornite
	 * Assegna di default un punto di fuga in cui si piazzerà il giocatore quando esce dal pianeta e la direzione di fuga
	 * e flag enableCollisionLevelDetection = false
	 * @param _world 
	 * @param origin 
	 * @param texture 
	 * @param int 
	 * @param _bounds 
	 */
	PlanetEntity( SolarSystem *_world = NULL, Point2D origin = Point2D(0,0), Bitmap *texture = NULL, unsigned int _radius = 4, Vector _bounds = Vector( 2 ) );

	/**
	 * PreCondition: requisiti Entity::~Entity()
	 */
	virtual ~PlanetEntity();

	/**
	 * @brief Elimina le risorse occupate da questa'entità, eliminando anche il livello associato (PlanetLevel::Delete)
	 * PostCondition: il giocatore nel livello di questo pianeta non viene deallocato
	 */
	virtual void Delete( GameEngine* game );
	
	/**
	 * @brief Restituisce il riferimento al livello questo pianeta
	 * 
	 * @return PlanetLevel* 
	 */
	PlanetLevel *GetPlanetLevel();

	/**
	 * @brief Imposta il riferimento al livello questo pianeta, senza eliminare quello precedente
	 * 
	 * @param planet_world 
	 */
	void SetPlanetLevel( PlanetLevel *planet_world );

	/**
	 * @brief Aggiorna lo stato di esistenza di questo pianeta.
	 * viene eliminato ed il punteggio del giocatore è aggiornato se è stato liberato
	 * 
	 * @param game 
	 * @return true se è un entità significativa
	 * @return false altrimenti
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @brief Disegna nella viewport un cerchio vuoto con il raggio del pianeta
	 * 
	 * @param view 
	 */
	virtual void Draw( ViewPort *view );

	/**
	 * @brief Indica se la posizione del giocatore è interna al cerchio, 
	 * tramite un norma euclidea delle distanze
	 */
	virtual bool IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Entity *entity );

};