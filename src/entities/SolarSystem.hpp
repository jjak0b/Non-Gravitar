#pragma once

#include "Level.hpp"

class SolarSystem : public Level{
	public:
    unsigned int count_planets;

	/**
	 * @brief Costruttore di un livello sistema solare contenente uno specifco numero di pianeti
	 * @PreCondition: La dimensione del livello deve essere tale che contenga il numero di pianeti richiesti
	 * per poterli raffigurare correttamente senza farli collidere l'uno con l'altro in fase di generazione
	 * @param bounds dimensioni del livello
	 * @param number_of_planets 
	 */
	SolarSystem( Vector bounds, unsigned int number_of_planets = 1 );

	/**
	 * @brief Gestisce lo stato del sistema solare
	 * @PostCondition Se i pianeti sono tutti stati liberati, forza il giocatore a dirigersi verso il suo centro
	 * e imposta il prossimo livello da caricare = NULL,
	 * @param game 
	 * @return true se il livello è significativo
	 * @return false se il giocatore è al centro del sistema solare, quindi deve essere caricato un nuovo sistema solare
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @brief Genera le entità pianeta contenuti nel sistema solare,
	 * in posizioni casuali ma quasi equidistanti
	 * @param game 
	 */
    virtual void Generate( GameEngine *game );
};