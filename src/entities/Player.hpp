#pragma once
#include "Damageable.hpp"
#include "DynamicEntity.hpp"
#include "engine/GameConfig.h"

class GameEngine;
class Level;
class Projectile;
class PlayerBeam;

#define PLAYER_HEALTH 500
#define PLAYER_MAX_FUEL 1500
#define PLAYER_MAX_SPEED 20
#define PLAYER_MAX_ACCELERATION 150
#define PLAYER_FRICTION_COEFFICIENT 1.0

#define PLAYER_SCORE_BUNKER_DESTROYED 500
#define PLAYER_SCORE_PLANET_DESTROYED 5000

#define PLAYER_FIRE_DAMAGE 50

#define PLAYER_FIRE_DELAY 0.2
#define PLAYER_BEAM_DELAY 0.1

#define PLAYER_PROJECTILE_SPEED (PLAYER_MAX_SPEED + 5)
#define PLAYER_BEAM_SPEED 50

class Player : public DynamicEntity, public Damageable {
	protected:
	INPUT_TYPE lastInput; // l'ultimo input ricevuto
	Vector lastMove; // l'ultimo spostamento effettuato
	Vector *moveOverride; // spostamento obbligato dal gioco
	double fuel; // quantità di carburante rimanente
	double MaxFuel; // massima quantità di carburante
	unsigned int score; // contatore dei punti del giocatore
	double fireTime = 0; // tempo dal quale può sparare
	double beamTime = 0; // tempo dal quale può usare il raggio
	
	public:
	/**
	 * @brief Costruttore del giocatore
	 * 
	 * @param world 
	 * @param origin 
	 * @param health 
	 */
	Player( Level *world, Point2D origin, double health );

	virtual ~Player();

	virtual void Delete( GameEngine* game );

	/**
	 * @brief Aggiorna velocità, accelerazione, posizione, direzione e carburante del giocatore in base all'input dell'utente rivelato dall'engine
	 * Aggiorna i tempi di sparo del proiettile e del raggio
	 * @param game 
	 * @return true se l'entità risulta significativa
	 * @return false altrimenti
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @brief Disegna La texture dell'entità stessa l'interfaccia grafica che mostra
	 * vita, punteggio, e carburante attuali in alto a sinistra della ViewPort
	 * 
	 * @param view 
	 */
	virtual void Draw( ViewPort *view );

	/**
	 * @brief Restituisce true se l'input passato come parametro corrisponde all'input di fuoco.
	 * @param input Input da controllare
	 * @return bool
	*/
	bool ShouldFire(INPUT_TYPE input);
	
	/**
	 * @brief Restituisce true se l'input passato come parametro corrisponde all'input del raggio traente.
	 * @param input
	 * @return bool
	*/
	bool ShouldBeam(INPUT_TYPE input);

	/**
	 * @brief Genera un proiettile nel livello. Il proiettile ha come direzione quella passata come parametro.
	 * @param direction Direzione del proiettile
	 * @return Projectile* puntatore al proiettile generato
	*/
	Projectile *Fire( Vector direction );

	/**
	 * @brief Genera un raggio nel livello. Il raggio ha sempre direzione verso il basso.
	 * @return Beam* puntatore al raggio generato
	*/
	PlayerBeam *Fire_Beam();

	/**
	 * @brief Restituisce il vettore direzione corrispondente all'input inserito.
	 * Se l'input non corrisponde a nessuna viene restituito il vettore direzione nullo.
	 * @param input 
	 * @return Vector vettore direzione corrispondente
	 */
	Vector GetDirectionFromInput( INPUT_TYPE input );

	/**
	 * @brief Callback di gestione collisione del giocatore
	 * Gestisce il comportamento alla collisione con:
	 * - PlanetEntity
	 * - Projectile
	 * - PlayerProjectile
	 * - Bunker
	 * - Level
	 * @param game 
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );

	/**
	 * @brief Imposta il movimento che il giocatore deve compiere forzatamente durante l'update succesivo di questa entità alla chiamata di questo metodo.
	 * Impostare direction = NULL se si vuole annullare il movimento forzato, altrimenti esso viene mantenuto ad ogni Update
	 * PreCondition: la dimensione del vettore direzione deve essere la stessa del punto posizione ( origin )
	 * PostCondition: Se un moveOverride è stato già precedentemente impostato, esso viene deallocato e sostituito con questo.
	 * @param direction 
	 */
	void SetMoveOverride( Vector *direction );

	/**
	 * @brief Imposta il valore massimo del carburante.
	 * @param amount 
	 */
	void SetMaxFuel( double amount );

	/**
	 * @brief Imposta il valore attuale del carburante.
	 * @param amount 
	 */
	void SetFuel( double amount );

	/**
	 * @brief Restituisce il valore massimo del carburante.
	 * @return double
	 */
	double GetMaxFuel();

	/**
	 * @brief Restituisce il valore attuale del carburante.
	 * @return double
	 */
	double GetFuel();
	
	
	/**
	 * @brief Aggiunge al carburante attuale la quantità inserita come parametro.
	 * PreCondition: amount maggiore di zero
	 * @param amount
	 */
	void AddFuel( double amount );

	/**
	 * @brief Rimuove dal carburante attuale la quantità inserita come parametro.
	 * PreCondition: amount maggiore di zero
	 * @param amount
	 */
	void RemoveFuel( double amount );

	/**
	 * @brief Restituisce il punteggio.
	 * @return unsigned int
	 */
	unsigned int GetScore();

	/**
	 * @brief Aggiunge al punteggio il valore passato come parametro.
	 * @param value
	 */
	void AddScore( unsigned int value );
};
