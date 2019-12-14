#pragma once
#include "Projectile.hpp"

/**
 * @brief Entità proiettile che implementa il comportamento del callback
 * del proiettile del giocatore
 * 
 */
class PlayerProjectile : public Projectile {


	public:
	PlayerProjectile( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed, double damage );
	/**
	 * @brief Callback specifico per gestire la collsione del proiettile del giocatore
	 * Se collide con il giocatore l'entità lo ignora
	 * altrimenti si comporta come Projectile::Callback_OnCollide
	 * @param game 
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};