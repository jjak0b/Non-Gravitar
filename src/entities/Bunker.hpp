#pragma once

#include "Entity.hpp"
#include "Damageable.hpp"

class Projectile;

#define BUNKER_FIRE_DAMAGE 1
#define BUNKER_HEALTH 5
/**
 * @brief Entità bunker rappresentate il nemico da distruggere
 * 
 */
class Bunker : public Entity, public Damageable {
	protected:
	double timer = 0; // tempo in cui è stato effettuato l'ultimo sparo

	public:
		Bunker( Level *world, Point2D origin, double health, const char classname[] );

		/**
		 * @brief Aggiorna il punteggio del giocatore in caso di distruzione del bunker
		 * Nota: non ha alcuna implementazione della logica di fuoco di un proiettile
		 * @param game 
		 * @return true 
		 * @return false 
		 */
		virtual bool Update(GameEngine* game);

		/**
		 * @brief Genera un proiettile aventi posizione direzione specificata.
		 * @param projectile_origin Origine del proiettile.
		 * @param direction Direzione del proiettile.
		 */
		Projectile *Shoot(Point2D projectile_origin, Vector direction );

		/**
		 * @brief Gestisce il comportamento di collisione tra questa entità e:
		 * - Player
		 * - PlayerProjectile
		 * 
		 * @param game 
		 * @param collide_ent 
		 */
		virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );

	
};