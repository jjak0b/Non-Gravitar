#pragma once

#include "DamageableEntity.hpp"
#include "Level.hpp"
#include "Vector.hpp"
#include "GameConfig.h"

class Player : public DamageableEntity{
	INPUT_TYPE lastInput; // l'ultimo input ricevuto
	Vector lastMove; // l'ultimo spostamento effettuato
	public:
	Player( Level *world, Point2D origin, double health );
	bool Update( GameEngine *game );
	bool ShouldFire(INPUT_TYPE input);
	bool ShouldBeam(INPUT_TYPE input);
	Projectile *Fire( Vector direction );
	Vector GetDirectionFromInput( INPUT_TYPE input );
	void SetLastInput( INPUT_TYPE input );
	INPUT_TYPE GetLastInput();
	Vector GetLastMove();
	void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
	/**
	 * @brief il giocatore abbandona il mondo corrente, viene aggiunto al livello specificato, e lo assegna come suo mondo in cui risiede
	 * 
	 * @param world 
	 */
	void SetWorld( Level *world );
};
