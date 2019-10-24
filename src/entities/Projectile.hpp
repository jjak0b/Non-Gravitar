#pragma once
#include "DynamicEntity.hpp"

class Projectile : public DynamicEntity{
	protected:
	double damage; // danno che infligge a qualsiasi entità che colpisce
	Vector direction; // vettore che indica la direzione dell'entità
	double lifetime; // tempo di esistenza di questo proiettile, prima di essere eliminato
	double deathtime; // tempo di gioco, in cui dovrà essere eliminato questa entità

	public:
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

	virtual bool Update( GameEngine *game );

	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};