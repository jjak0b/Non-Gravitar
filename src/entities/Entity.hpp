#pragma once

#include "shared/Point2D.hpp"
#include "engine/Bitmap.hpp"
#include "shared/Shape.hpp"
#include <stddef.h> // usato per definizione di NULL

class Level;
class GameEngine;
class ViewPort;

class Entity{
protected:
	Level *world = NULL;
	Point2D origin ; // Coordinate dell'entità nel mondo di gioco
	Bitmap *texture = NULL; // puntatore alla texture che verrà visualizzata quando è questa entità è visibile nella ViewPort
	char *str_classname = NULL; // nome della classe che specifica il tipo di questa entità
	bool garbage = false; // indica se questa entità dovrebbe essere cancellata
	bool shouldDeleteOnUpdate = false; // che che indica se l'entità deve essere eliminata in Entity::Update
	Shape *shape = NULL;
	bool isCollidable;
	bool enableCollisionLevelDetection;

public:
	Entity( Level *world, Point2D origin, Bitmap *texture = NULL, const char classname[] = "", Shape *shape = NULL );

	/**
	 * PreCondition: chiamare prima Delete( GameEngine* ) prima di deallocare tramite costruttore.
	 */
	virtual ~Entity();

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
	virtual Point2D SetOrigin( const Point2D origin );

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
	virtual void Draw( ViewPort *view );

	/**
	 * @brief Aggiorna lo stato di questa entità quale la posizione, funzionalità e logica che deve avere nel gioco
	 * 
	 * @param game 
	 * @return true la questa entità esisterà anche il prossimo frame.
	 * @return false questa entità dovrà essere eliminata 
	 */
	virtual bool Update( GameEngine *game );

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
	virtual void Delete( GameEngine* game );

	/**
	 * @brief Verifica se questa entità sta collidendo con quella specificata,
	 * PreCondition: impostare puntatore collisionOrigin = NULL se non si vuole ottenere il punto di collisione
	 * PostCondition: se avviene una collisione: il valore puntato da collisionOrigin contiene la posizione di collisione
	 * @param entity : entità da controllare
	 * @return true se è avvenuta una collisione
	 * @return false altrimenti
	 */

	virtual bool IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
							GameEngine* game,
#endif
							Entity *entity);


	Shape* GetShape();

	void SetShape( Shape *shape );
	
	bool IsCollidable() const;
	
	void setIsCollidable(bool isCollidable);
	
	/**
	 * @brief funzione di callback o risposta che deve essere richiamata nel caso questa entità collida con un altra
	 * e ne gestirà il comportamento
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );

	/**
	 * @brief Indica se questa entità si trova in una posizione esterna al pianeta preso in considerazione
	 * 
	 * @param entity 
	 * @return true 
	 * @return false 
	 */
	bool IsOutOfTheWorld();




};