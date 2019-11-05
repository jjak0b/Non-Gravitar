#pragma once
#include "Entity.hpp"

class Fuel : public Entity{
	protected:
	double healthSize; // Punti salute che il giocatore guadagna quando colpisce il fuel con il raggio traente.
	double fuelSize; // punti carburante guadagnati
	public:
	Fuel( Level *world, Point2D origin );
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};