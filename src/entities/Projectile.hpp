#pragma once
#include "DynamicEntity.hpp"

class Projectile : public DynamicEntity{
	protected:
	double damage; // danno che infligge a qualsiasi entità che colpisce
	Vector direction; // vettore che indica la direzione dell'entità
	double lifetime; // tempo di esistenza di questo proiettile, prima di essere eliminato
	double deathtime; // tempo di gioco, in cui dovrà essere eliminato questa entità

	public:
	/**
	 * @brief Costruttore di un'entità proiettile avente una specifica direzione di movimento ed una velocità costante
	 * @PostCondition: l'entità è eliminata quando il suo tempo di vita è passato
	 * @param world 
	 * @param origin 
	 * @param direction 
	 * @param damage 
	 * @param classname 
	 * @param speed 
	 * @param lifetime 
	 */
	Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed = 10, double lifetime = 4.0 );

	/**
	 * @brief Restituisce il danno del proiettile.
	 * @return double
	 */
	double GetDamage();

	/**
	 * @brief Restituisce la direzione del proiettile.
	 * @return double
	 */
	Vector GetDirection();

	/**
	 * @brief Aggiorna il tempo di vita di questa entità e la sua velocità
	 * 
	 * @param game 
	 * @return true 
	 * @return false 
	 */
	virtual bool Update( GameEngine *game );

	/**
	 * @brief Gestisce il comportamento di collisione di questa entità
	 * forzando la cancellazione di questo proiettile al prossimo frame
	 * 
	 * @param game 
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};