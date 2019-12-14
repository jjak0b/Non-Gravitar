#pragma once

#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "shared/Utility.h"

struct ent_generation_info {
	Utility::range_t<float> probability;
	Utility::range_t<size_t> count;
};

struct surface_generation_info {
    Utility::range_t<VECTOR_VALUE_TYPE> distance_x;
    Utility::range_t<VECTOR_VALUE_TYPE> distance_y;
    Utility::range_t<VECTOR_VALUE_TYPE> bound_y;
	bool isGeneratingNegativeDone;
	bool isGeneratingPositiveDone;
};

struct generation_info_table {
	ent_generation_info info_bunkers;
	ent_generation_info info_fuels;
	surface_generation_info info_surface;
};

class PlanetEntity;

class PlanetLevel : public Level{

private:
	generation_info_table generation_status; // struttura contenente informazioni sullo stato di generazione
	
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
	 * PostCondition: quando il giocatore abbandona il pianeta, cambia prossimo livello da caricare
	 * con quello dell livello in cui risiede Planet Entity
	 * @param game 
	 * @return false se il giocatore abbandona il pianeta
	 * @return true altrimenti
	 */
	virtual bool Update( GameEngine *game );
    
	/**
	 * @brief Genera il Livello di gioco, generando casualmente il terreno e le sue entità bunker e fuel,
	 * secondo la distanza di della schermata data dalla ViewPort del giocatore a runtime, quindi la generazione è procedurale
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
	
private:
	/**
	 * @Brief Tenta la generazione nel punto specificato di un entità Bunker o fuel con le probabilità in generation_status.info_...
	 * @PostCondition Se l'entità è stata generata, esse viene automaticamente aggiunta alla lista delle entità di questo livello
	 * @param spawnPoint punto in cui generare l'entità
	 * @return il puntatore all'entità generata (NULL se non è stato generata )
	 */
	Entity* TryGenerateRandomEntity( Point2D spawnPoint );

	/**
	 * @Brief Genera un offset casuale secondo i vincoli e distanze in generation_status.info_surface
	 * @param previous punto precedente generato nella stessa direzione direzione
	 * @param generation_direction può essere <,> o = 0: consiste nel coeeficiente di direzione
	 * della generazione del punto sulla componente ciclica x
	 * @return
	 */
	Point2D GenerateRandomSurfaceOffset( Point2D previous, int generation_direction );
};