#pragma once

#include "DynamicEntity.hpp"
class Damageable;

class Projectile : public DynamicEntity{
	protected:
	double damage; // danno che infligge a qualsiasi entità che colpisce
	Point2D fireOrigin; // punto di partenza da cui è stato generato il proiettile
	Vector direction; // vettore che indica la direzione dell'entità
	double lifetime ;
	

	public:
	Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed = 10 );

	Point2D GetFireOrigin();

	double GetDamage();

	Vector GetDirection();

	virtual bool Update( GameEngine *game ); // aggiorna lo stato del proiettile, come la posizione, ecc...

	virtual void Draw( ViewPort *view );

	/**
	 * @brief funzione risposta / callback che dovrà essere chiamata quando questo proiettile ha colpito una qualche entità
	 * @param collide_ent
	 */
	void Callback_OnCollide();
	void Callback_OnCollide( Damageable* entity );



};