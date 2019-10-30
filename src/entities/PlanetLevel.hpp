#pragma once

#include "Level.hpp"
#include "engine/GameEngine.hpp"

class PlanetEntity;

class PlanetLevel : public Level{
	protected:

	

	/**
	 * @brief Entità associata a questo livello:
	 * Quando il giocatore esce dal livello, nel frame successivo verranno aggiornati e visualizzati
	 * gli elementi del mondo in cui risiede questo PlanetEntity
	 */
	PlanetEntity *planet_entity;

	public:
	
	/**
	 * @brief Istanzia un nuovo livello con la logica del pianeta,
	 * il pianeta ha un propria longitudine e altitudine massima, rispettivamente recuperabili tramite GetWidth e GetHeight
	 * 
	 * @param planet_entity : riferimento dell' entità pianeta che risiede nel sistema solare, a cui è asspociato questo livello
	 * @param bounds( max_longitude, max_altitude )
	 * @param 
	 */
	PlanetLevel( PlanetEntity *planet_entity = NULL, Vector bounds = Vector( 2 ) );

	virtual void Delete( GameEngine* game );
	
	/**
	 * @brief Restituisce il riferrimento all'entità pianeta a cui questo livello è associato
	 * 
	 * @return PlanetEntity* 
	 */
	PlanetEntity *GetPlanetEntity();

	/**
	 * @brief Imposta l'entità pianeta a cui questo livello deve essere associato
	 * 
	 * @param entity 
	 */
	void SetPlanetEntity( PlanetEntity *entity );

	/**
	 * @brief funzione di aggiornamento degli stati delle delle entità
	 * PostCondition: quando il giocatore abbandona il pianeta, questo livello sarà flaggato come IsGarbage
	 * @param game 
	 * @return false se il giocatore abbandona il pianeta
	 * @return true altrimenti
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @Brief: vedere Level::ShouldGenerate
	 * @param view
	 */
    virtual int ShouldGenerate(ViewPort *view);

	/**
	 * @brief Genera il Livello di gioco, generando il terreno e le sue entità,
	 * se è stato generato in precedenza esso viene rigenerato ( sempre casualmente )
	 * 
	 * @param game 
	 */
	virtual void Generate( GameEngine *game );

	/**
	 * @brief Indica se il pianeta e privo di bunker
	 * 
	 * @return true se i bunker non stati distrutti
	 * @return false altrimenti
	 */
	bool IsFree();

	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
	
};