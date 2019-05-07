#pragma once

#include "Point2D.hpp"
#include "ColoredBitmap.hpp"
#include "Viewport.hpp"
#include <stddef.h> // usato per definizione di NULL
class Level;
class GameEngine;

class Entity{
protected:
	Level *world = NULL;
	Point2D origin; // Coordinate dell'entità nel mondo di gioco
	ColoredBitmap *texture = NULL; // puntatore alla texture che verrà visualizzata quando è questa entità è visibile nella ViewPort
	char *str_classname = NULL; // nome della classe che specifica il tipo di questa entità
	bool garbage = false; // indica se questa entità dovrebbe essere cancellata
public:
	Entity( Level *world, Point2D origin, ColoredBitmap *texture = NULL, const char classname[] = "" );

	/**
	 * @brief Restituisce il riferimento del livello in cui "risiede" l'entità
	 * 
	 * @return Level* 
	 */
	Level *GetWorld();

	/** 
	 * @brief Imposta il livello di riferimento in cui risiede l'entità, senza deallocare quello già impostato
	 * 
	 * @param world 
	 */
	void SetWorld( Level *world );

	/**
	 * @brief Imposta la posizione attuale dell'entità nel mondo
	 * PostCondition: le coordinate saranno normalizzate in base alle dimensioni (limiti) del mondo
	 * @param origin 
	 * @return Point2D : le coordinate normalizzate al mondo
	 */
	Point2D SetOrigin( Point2D origin );

	/**
	 * @brief Restituisce la posizione attuale di questa entità nel mondo
	 * @return Point2D
	 */
	Point2D GetOrigin();

	/**
	 * @brief Restituisce il nome della tipologia di entità
	 * PostCondition: il valore restituito è un puntatore ad un stringa,
	 * Nota: il valore restituito non è una nuova allocazione di una nuova stringa
	 * @return char* 
	 */
	char *GetClassname();

	/**
	 * @brief Disegna l'entità nella viewport asssociata all camera di gioco,
	 * se l'entità si trova parzialmente nella finestra della viewport, ne verrà visualizzata solo la parte interna alla viewPort
	 * Es se la ViewPort sono disegnate le entità da Xi a Xf, e questa entità si trova a Xi-(L) allora verrà
	 * disegnata solo la porzione P (> L) della texture che parte da Xi
	 * se la texture associata è NULL, viene disegnato solo un pixel
	 * @param view : gestore che si occupa di gestire i frame degli oggetti visibili all'interno del gioco
	 */
	void Draw( ViewPort *view );

	/**
	 * @brief Aggiorna lo stato di questa entità quale la posizione, funzionalità e logica che deve avere nel gioco
	 * 
	 * @param game 
	 * @return true la questa entità esisterà anche il prossimo frame.
	 * @return false questa entità dovrà essere eliminata 
	 */
	bool Update( GameEngine *game );

	/**
	 * @brief Indica se questa entità è significativa in gioco ( false ) o dovrebbe essere cancellata ( true )
	 * @return true 
	 * @return false 
	 */
	bool IsGarbage();

	/**
	 * @brief prepara questa entità per essere eliminata,
	 * PostCondition: dopo essere chiamata deve effettuare il delete comunque per essere deallocata
	 */
	void Delete();

	/**
	 * @brief Verifica se questa entità sta collidendo con quella specificata,
	 * PreCondition: impostare puntatore collisionOrigin = NULL se non si vuole ottenere il punto di collisione
	 * PostCondition: se avviene una collisione: il valore puntato da collisionOrigin contiene la posizione di collisione
	 * @param entity : entità da controllare
	 * @param collisionOrigin : punto di collisione
	 * @return true se è avvenuta una collisione
	 * @return false altrimenti
	 */
	bool IsColliding( Entity *entity, Point2D *collisionOrigin);

	/**
	 * @brief funzione di callback o risposta che deve essere richiamata nel caso questa entità collida con un altra
	 * e ne gestirà il comportamento
	 * @param collide_ent 
	 * @param hitOrigin 
	 */
	void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );

	/**
	 * @brief Indica se questa entità si trova in una posizione esterna al pianeta preso in considerazione
	 * 
	 * @param entity 
	 * @return true 
	 * @return false 
	 */
	bool IsOutOfTheWorld();
};