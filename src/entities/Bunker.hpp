#pragma once

#include "Entity.hpp"
#include "Damageable.hpp"

class Projectile;

class Bunker : public Entity, public Damageable {
	protected:
	double timer = 0;

	public:
		Bunker( Level *world, Point2D origin, double health, const char classname[] );

		virtual bool Update(GameEngine* game);

		/**
		 * @brief Genera un proiettile.
		 * PreCondition: projectile_origin e direction diversi da NULL.
		 * @param projectile_origin Origine del proiettile.
		 * @param direction Direzione del proiettile.
		 */
		Projectile *Shoot(Point2D projectile_origin, Vector direction );

		virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );

	
};