#pragma once

#include "Entity.hpp"

// indici componenti vettoriali dei limiti del mondo
#define BOUND_INDEX_WIDTH 0
#define BOUND_INDEX_HEIGHT 1

class GameEngine;
class Player;

class Level : public Entity{
protected:
	Vector bounds; // limiti del mondo ( dimensioni del livello )
	Player *player; // Riferimento del giocatore se risiede in questo livello
	list<Entity*> entities; // lista della entità presenti nel livello
	bool isGenerated; // indica se il livello è stato completamente generato
public:
	/**
	 * @brief Costruttore nel livello
	 * Nota: il livello di un livello è se stesso
	 */
	Level( Vector _bounds = Vector( 2 ), const char _className[] = "Level" );
	/**
	 * PreCondition: requisiti Entity::~Entity()
	 */
	virtual ~Level();

	/**
	 * @brief Aggiorna lo stato delle entità del mondo, verificando prima gli stati di collisione e richiamando internamente i loro metodi Update( ... )
	 * Restituisce true 
	 * PostCondition: Elimina le entità il cui metodo Update( ... ) restituisce valore false o non risultano più significative, quindi ne invoca il metodo Delete()
	 * ( Player::Delete non è richiamato )
	 * @param game 
	 * @return true se il livello è significativo
	 * @return false altrimenti oppure se l'entità del giocatore non risulta più significativa
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @brief Disegna nella Viewport i segmenti che costituiscono la forma del livello
	 * e tutte le sue entità, richiamando i loro metodi Draw( ... )
	 * @param view 
	 */
	virtual void Draw( ViewPort* view );

	/**
	 * @brief Interfaccia Dedicata per generare il Livello di gioco, generando il terreno e le sue entità,
	 * secondo la logica di generazione del livello stesso
	 * @param game 
	 */
	virtual void Generate( GameEngine *game );

	/**
	 * @brief Adatta il punto in base alle dimensioni del mondo: 
	 * se una componente del punto supera il limite del mondo per quella componente,
	 * ricomincierà dall'inizio del mondo in modulo ( coordinata 0 ) + il valore della componente rimanente
	 * @param origin 
	 * @return Point2D 
	 */
	Point2D GetNormalizedPoint( Point2D origin );

	/**
	 * @brief restituisce il Vettore aventi i limiti massimi del livello, nelle sue Vector.GetSize() dimensioni
	 * 
	 * @return Vector 
	 */
	Vector GetBounds();

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
	 * @brief Aggiunge l'entità alla lista delle entità nel mondo, e assegna questo livello come suo mondo in cui risiede.
	 * PostCondition: Se prima risiedeva in un altro livello, esso viene prima rimosso da esso
	 * Nota: Per rimuovere un entità, essa deve essere eliminata oppure spostata in altro livello richiamanto comunque questo metodo
	 * @param entity 
	 */
	void AddEntity( Entity *entity );

	/**
	 * @brief Elimina le entità nel mondo, deallocando le risorse occupate
	 * PostCondition: il giocatore non verrà eliminato, quindi deve essere rimosso prima di richiamare questo metodo
	 */
	virtual void Delete( GameEngine* game );

	/**
	 * @brief Restituisce la lista di puntatori alle entità presenti nel mondo (incluso il giocatore in essa ), in base alle seguenti condizioni
	 * ( Nota: Sia '€' simbolo di appartenza )
	 * se str_className != NULL
	 * 		se b_exclude == true list = { e € entities | e.GetClassname() != str_className }
	 * 		se b_exclude == false list = { e € entities | e.GetClassname() = str_className }
	 * altrimenti
	 * 		list = { entities }
	 * Nota: se b_search_className_as_subString == true invece di effettuare un esatto confronto, verifica se str_className € e.GetClassname
	 * PreCondition: se str_className != NULL deve essere una stringa
	 * PostCondition: se str_classname == NULL la lista contiene tutte le entità del mondo ignorando il filtro, e b_exclude
	 * @param str_className 
	 * @param b_exclude 
	 * @param b_search_className_as_subString
	 * @return list<Entity*> 
	 */
	list<Entity*> GetEntities( const char *str_className, bool b_exclude, bool b_search_className_as_subString );

	/**
	 * @brief Rimuove Il giocatore dal livello, restituendone il riferimento
	 * 
	 * @return Player* 
	 */
	Player *GetOutPlayer();

	/**
	 * @brief Indica se la superficie del livello è stato generata
	 * 
	 * @return true se la superficie del livello è stata generata
	 * @return false altrimenti
	 */
	virtual bool IsGenerated();

	private:
	/**
	 * @brief Non fa niente, ma viene nascosta la visibilità esterna tramite overriding
	 */
	void SetOrigin();

	
};
