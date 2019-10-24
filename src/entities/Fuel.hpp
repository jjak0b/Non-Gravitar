#pragma once
#include "Entity.hpp"

class Fuel : public Entity{
	protected:
	double size; // Punti salute che il giocatore guadagna quando colpisce il fuel con il raggio traente.

	public:
	Fuel( Level *world, Point2D origin );
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};