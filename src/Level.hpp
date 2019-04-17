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
	Entity *StaticEnts; // Entità statiche del mondo ( Bunker, carburante )
	// List *DynamicEnts // Entità dinamiche del mondo ( Proiettili, etc... )
	Player *player; // il giocatore dovrebbe essere tra le StaticEnts ? ( per esempio in StaticEnts[0] )
	// List *WorldPoints // lista dei Point2D che costruiscono il terreno
	list<Entity*> entities;
	list<Projectile*> projectiles;
	list<Fuel*> fuel;
public:
	/**
	 * @brief Istanzia tutte le entità nel mondo, genera il terreno e le entità del livello
	 * PostCondition: se player != NULL allora esso non viene reinstanziato
	 */
	Level( unsigned int MaxWidth, unsigned int MaxHeight, Player *player );

	/**
	 * @brief Aggiorna lo stato delle entità del mondo, richiamando internamente i loro metodi Update( ... )
	 * PostCondition: Dealloca le entità il cui metodo Update( ... ) restituisce valore false, quindi ne invoca il metodo Delete()
	 * @param game 
	 */
	void Update( GameEngine *game );

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
	 * @brief Aggiunge l'entità alle lista delle entità nel mondo
	 * @param entity 
	 */
	void AddEntity( Entity *entity );

	/**
	 * @brief Verifica se l'entità specificata collide con il terreno di gioco
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
	list<Entity*> Level::GetEntities( const char *str_className, bool b_exclude );

	private:
	/**
	 * @brief Non fa niente, ma viene nascosta la visibilità esterna tramite overriding
	 */
	void SetOrigin();
};