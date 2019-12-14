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
	Level *world; // livello di gioco in cui questa entità risiede
	Point2D origin ; // Coordinate dell'entità nel mondo di gioco
	Bitmap *texture; // puntatore alla texture che verrà visualizzata quando è questa entità è visibile nella ViewPort
	char *str_classname; // nome della classe che specifica il tipo di questa entità
	bool garbage; // indica se questa entità dovrebbe essere cancellata, quindi non più significativa
	bool shouldDeleteOnUpdate; // indica se l'entità deve essere resa non significativa in Entity::Update
	Shape *shape; // figura di collisione associata a questa entità
	bool isCollidable; // indica se questa entitò può collidere. sse = true il controllo di collisione è effettuato
	bool enableCollisionLevelDetection; // indica se dovrebbe essere effettuato il controllo di collisione tra questa entità e il livello

public:
	/**
	 * @brief Construttore dell'entità
	 * Internamente il classname è un duplicato della stringa C fornita.
	 * Di default questi flag sono impostati come segue:
	 * isCollidable = true;
	 * enableCollisionLevelDetection = true;
	 * @PostCondition:
	 * classname non deve essere in alcun modo modificato per tutta l'esecuzione del gioco.
	 * L'entità è aggiunta automaticamente al livello specificato se != NULL
	 * 
	 * @param world 
	 * @param origin 
	 * @param texture 
	 * @param classname 
	 * @param shape 
	 */
	Entity( Level *world, Point2D origin, Bitmap *texture = NULL, const char classname[] = "", Shape *shape = NULL );

	/**
	 * @brief Distruttore dell'entità e di tutte le risorse che utilizza
	 * @PreCondition: chiamare prima Delete( GameEngine* ) prima di deallocare tramite costruttore.
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
	 * @PreCondition: Ogni sottoclasse deve richiamare prima l'Update di ogni superclasse fino a richiamare questo
	 * @param game 
	 * @return true la questa entità risulta significativa
	 * @return false questa entità non risulta più significativa
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
	 * @param entity : entità da controllare
	 * @return true se è avvenuta una collisione
	 * @return false altrimenti
	 */

	virtual bool IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
							GameEngine* game,
#endif
							Entity *entity);


	/**
	 * @brief Restituisce il riferimento alla forma di collisione
	 * 
	 * @return Shape* 
	 */
	Shape* GetShape();

	/**
	 * @brief Imposta il riferimento alla forma di collisione
	 * 
	 * @param shape 
	 */
	void SetShape( Shape *shape );
	
	/**
	 * @brief Indica se questa entità può collidere
	 * 
	 * @return true 
	 * @return false 
	 */
	bool IsCollidable() const;
	
	/**
	 * @brief funzione di callback o risposta che deve essere richiamata nel caso questa entità collida con un altra
	 * e ne gestirà il comportamento
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );

	/**
	 * @brief Indica se questa entità si trova in una posizione esterna al livello preso in considerazione
	 * 
	 * @param entity 
	 * @return true 
	 * @return false 
	 */
	bool IsOutOfTheWorld();

};