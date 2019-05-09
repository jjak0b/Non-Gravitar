#pragma once

#include "Level.hpp"

class PlanetEntity;

class PlanetLevel : public Level{
	protected:
	PlanetEntity *planet_entity;

	public:
	/**
	 * @brief Istanzia un nuovo livello con la logica del pianeta,
	 * il pianeta ha un propria longitudine e altitudine massima, rispettivamente recuperabili tramite GetWidth e GetHeight
	 * 
	 * @param planet_entity : riferimento dell' entità pianeta che risiede nel sistema solare, a cui è asspociato questo livello
	 * @param max_longitude
	 * @param max_altitude
	 * @param player : riferimento del giocatore se viene aggiunto a questo livello
	 */
	PlanetLevel( PlanetEntity *planet_entity = NULL, unsigned int max_longitude = 0, unsigned int max_altitude = 0 );

	/**
	 * @brief funzione di aggiornamento degli stati delle delle entità
	 * PostCondition: quando il giocatore abbandona il pianeta, questo livello sarà flaggato come IsGarbage
	 * @param game 
	 * @return false se il giocatore abbandona il pianeta
	 * @return true altrimenti
	 */
	bool Update( GameEngine *game );

	/**
	 * @brief Restituisce il riferrimento all'entità pianeta a cui questo livello è associato
	 * 
	 * @return PlanetEntity* 
	 */
	PlanetEntity *GetPlanetEntity();

	/**
	 * @brief Indica se il pianeta e privo di bunker
	 * 
	 * @return true se i bunker non stati distrutti
	 * @return false altrimenti
	 */
	bool IsFree();
};