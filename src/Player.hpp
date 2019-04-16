#pragma once

#include "DamageableEntity.hpp"
#include "Level.hpp"
#include "Vector.hpp"

class Player : public DamageableEntity{
	char lastInput; // l'ultimo input ricevuto
	Vector lastMove; // l'ultimo spostamento effettuato
	public:
	Player( Level *world, Point2D origin, double health );
	void Update( GameEngine *game );
	bool ShouldFire(char input);
	bool ShouldBeam(char input);
	Projectile *Fire( Vector direction );
	Vector GetDirectionFromInput( char input );
	void SetLastInput( char input );
	char GetLastInput();
	Vector GetLastMove();
};
