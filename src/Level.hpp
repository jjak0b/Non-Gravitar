#pragma once

#include "Entity.hpp"
#include "Projectile.hpp"
#include "Fuel.hpp"
#include "Point2D.hpp"

#include <list>
using namespace std;

class GameEngine;
class Player;

class Level : public Entity{
protected:
	unsigned int width, height; // dimensioni del mondo
	Player *player; // il giocatore dovrebbe essere tra le StaticEnts ? ( per esempio in StaticEnts[0] )
	// list<Point2D*> surface; // lista dei punti che costruiscono il terreno
	list<Entity*> entities;
public:
	/**
	 * @brief Istanzia tutte le entità nel mondo, genera il terreno e le entità del livello
	 * PostCondition: se player != NULL allora esso non viene reinstanziato
	 */
	Level( Level *parentWorld = NULL, unsigned int MaxWidth = 0, unsigned int MaxHeight = 0, const char _className[] = "", Player *player = NULL );

	/**
	 * @brief Aggiorna lo stato delle entità del mondo, richiamando internamente i loro metodi Update( ... )
	 * Restituisce true se il giocatore si trova in questo Livello, altrimenti se lo ha
	 * PostCondition: Dealloca le entità il cui metodo Update( ... ) restituisce valore false, quindi ne invoca il metodo Delete()
	 * @param game 
	 */
	bool Update( GameEngine *game );

	/**
	 * @brief Disegna nella Viewport tutte le entità del mondo, richiamando internamente i loro metodi Draw( ... ) 
	 * @param view 
	 */
	void Draw( ViewPort* view );

	/**
	 * @brief Normalizza il punto in base alle dimensioni del mondo: 
	 * se una componente del punto supera il limite del mondo per quella componente,
	 * ricomincierà dall'inizio del mondo in modulo ( coordinata 0 ) + il valore della componente rimanente
	 * @param origin 
	 * @return Point2D 
	 */
	Point2D GetNormalizedPoint( Point2D origin );

	/**
	 * @brief Restituisce la dimensione massima del mondo nell'asse X
	 * @return unsigned int 
	 */
	unsigned int GetMaxWidth();
	/**
	 * @brief Restituisce la dimensione massima del mondo nell'asse Y
	 * @return unsigned int 
	 */
	unsigned int GetMaxHeight();

	/**
	 * @brief Restituisce il puntatore al giocatore
	 * 
	 * @return Player* 
	 */
	Player *GetPlayer();

	/**
	 * @brief Aggiunge l'entità alla lista delle entità nel mondo, e assegna questo livello come suo mondo in cui risiede
	 * @param entity 
	 */
	void AddEntity( Entity *entity );

	/**
	 * @brief Rimuove l'entità dalla lista delle entità, senza deallocare l'entità stessa
	 * Inoltre il suo mondo in cui risiede è = NULL
	 * @param entity 
	 */
	void RemoveEntity( Entity *entity );

	/**
	 * @brief Verifica se l'entità specificata collide con il mondo di gioco
	 * PreCondition: impostare puntatore collisionOrigin = NULL se non si vuole ottenere il punto di collisione
	 * PostCondition: se avviene una collisione: il valore puntato da collisionOrigin contiene la posizione di collisione
	 * @param entity 
	 * @return true 
	 * @return false 
	 */
	bool IsColliding( Entity *entity, Point2D *collisionOrigin );

	/**
	 * @brief Elimina le entità nel mondo, deallocando le risorse occupate
	 * se b_delete_player = true, il giocatore verrà deallocato
	 * @param b_delete_player 
	 */
	void Delete( bool b_delete_player );

	/**
	 * @brief Restituisce la lista di puntatori alle entità presenti nel mondo,
	 * se str_className è specificato, la lista contiene solo entità della classe specificata
	 * PreCondition: se str_className != NULL deve essere una stringa
	 * PostCondition: se str_classname == NULL la lista contiene tutte le entità del mondo senza filtri
	 * @param str_className 
	 * @return list<Entity*> 
	 */

	/**
	 * @brief Restituisce la lista di puntatori alle entità presenti nel mondo,
	 * se str_className != NULL
	 * 		se b_exclude == true list = { e € entities | e.GetClassname() != str_className }
	 * 		se b_exclude == false list = { e € entities | e.GetClassname() == str_className }
	 * altrimenti
	 * 		list = { entities }
	 * PreCondition: se str_className != NULL deve essere una stringa
	 * PostCondition: se str_classname == NULL la lista contiene tutte le entità del mondo ignorando il filtro, e b_exclude
	 * @param str_className 
	 * @param b_exclude 
	 * @return list<Entity*> 
	 */
	list<Entity*> GetEntities( const char *str_className, bool b_exclude );

	/**
	 * @brief Rimuove Il giocatore dal livello, restituendone il riferimento
	 * 
	 * @return Player* 
	 */
	Player *GetOutPlayer();

	private:
	/**
	 * @brief Non fa niente, ma viene nascosta la visibilità esterna tramite overriding
	 */
	void SetOrigin();
};

/**
 * @brief Richiama il metodo Update(...) dell'entità in base alla sua classe ( come se i metodi Update delle entità fossero virtual ); e ritorna il valore restituito da Update
 * 
 * @param game 
 * @param entity 
 * @return bool 
 */
bool EntityUpdateSelector( GameEngine *game, Entity *entity );

/**
 * @brief Richiama il metodo Draw(...) dell'entità in base alla sua classe ( come se i metodi Update delle entità fossero virtual )
 * 
 * @param view 
 * @param entity 
 */
void EntityDrawSelector( ViewPort *view, Entity *entity );