#pragma once

#include <iostream>
#include "Viewport.hpp"
#include "GameConfig.h"
#include "entities/SolarSystem.hpp"

class GameEngine{
private:
	ViewPort *view; // ViewPort principale contenente il contesto grafico del frame attuale, cioè la schermata di gioco
	INPUT_TYPE input_key; // ultimo inout rivelato per il frame
	double time; // tempo di esecuzione del gioco
	double deltaTime; // differenza di tempo dall'ultima esecuzione del frame precedente
	Level *currentLevel; // livello in esecuzione
	list<Entity*> garbage_collector; // lista di entità contenente i puntatori delle entità considerate da deallocare alla fine del frame
public:

	GameEngine( unsigned int screen_width = DEFAULT_WINDOW_WIDTH, unsigned int screen_height = DEFAULT_WINDOW_HEIGHT );

	/**
	 * @brief Aggiorna la dimensione della ViewPort in base alle nuove dimensioni, il tempo di esecuzione, e l'ultimo input fornito
	 * 
	 * @param deltaTime tempo passato dall'ultimo frame
	 * @param key_pressed ultimo input rilevato dall'ultimo frame
	 * @param width larghezza della finestra UI
	 * @param height altezza della finesta UI
	 * @return true se la dimensione della ViewPort è stata aggiornata
	 * @return false altrimenti perchè risultano uguali a quelle precedenti.
	 */
	bool update( double deltaTime, INPUT_TYPE key_pressed, unsigned int width, unsigned int height );

	/**
	 * @brief logica del motore grafico per avvia la fase di aggiornamento del livello.
	 * In caso il livello non sia allocato, genera casualmente un livello SolarSystem e lo carica.
	 * Si distengue in fasi consecutive:
	 * 	- Loading: Prepara il livello (se cambiato dal frame precdente) per il frame attuale
	 * 	- Updatig: Richiama il metodo Update del livello caricato
	 *  - Drawing: Richiama il metodo Draw del livello caricato
	 *  - Deleteing: dealloca le risorse occupate nel "garbage collector"
	 * In caso di GameOver dealloca la ViewPort
	 * @param dtime tempo passato dall'ultimo frame
	 * @return true Se il gioco può essere aggiornato nel frame successivo 
	 * @return false altrimenti perchè risulta in un GameOver
	 */
	bool frame( double dtime );

	/**
	 * @brief Restituisce il riferimento alla ViewPort
	 * @return ViewPort* 
	 */
	ViewPort* GetViewport();

	/**
	 * @brief Imposta la posizione iniziale della ViewPort in base a al sistema di coordinate del livello
	 * Per posizione iniziale della ViewPort si intende la coordinata del livello
	 * che inizia nel punto in basso a sinistra relativa alla Viewport 
	 * @param origin 
	 */
	void SetCameraWorldOrigin( Point2D origin );

	/**
	 * @brief Restituisce la posizione attuale della ViewPort
	 * Per posizione iniziale della ViewPort si intende la coordinata del livello
	 * che inizia nel punto in basso a sinistra relativa alla Viewport 
	 * @return Point2D 
	 */
    Point2D GetCameraWorldOrigin();

	/**
	 * @brief Restituisce l'ultimo input rivelato
	 * 
	 * @return INPUT_TYPE 
	 */
	INPUT_TYPE GetkeyPressed();

	/**
	 * @brief Restituisce il tempo di esecuzione del gioco
	 * 
	 * @return double 
	 */
	double GetTime();
	
	/**
	 * @brief Restituisce il tempo passato dall'ultimo frame
	 * 
	 * @return double 
	 */
	double GetDeltaTime();

	/**
	 * @brief Restituisce il riferimento al livello caricato attualmente
	 * 
	 * @return Level* 
	 */
	Level *GetCurrentLevel();

	/**
	 * @brief Assegna il livello da caricare (senza deaollocare quello precedente)
	 * 
	 * @param level 
	 */
	void SetCurrentLevel( Level *level );
	
	/**
	 * @brief Elimina il livello attuale e l'ultimo livello caricato aggiungendoli al garbage collector
	 * 
	 * @param last_loaded_level 
	 */
	void UnloadLevel( Level *last_loaded_level );

	/**
	 * @brief Effettua la deallocazione effettiva di tutte le entità presenti nel garbage collector
	 * cioè di tutte quelle che è stata richiamata Delete
	 */
	void ClearGarbageCollector();

	/**
	 * @brief Aggiunge l'entitò fornita al garbage collector
	 * per essere deallocata completamente al termine del frame
	 * @PostCondition se non impostata come garbage, allora richiama prima Delete su di essa
	 * @param entity 
	 */
	void AddGarbage(Entity *entity);
};


/**
 * @brief Verifica se l'entità è significativa nel gioco
 * 
 * @param entity 
 * @return true 
 * @return false 
 */
bool IsDefined( Entity *entity );
