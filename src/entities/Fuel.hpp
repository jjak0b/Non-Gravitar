#pragma once
#include "Entity.hpp"

/**
 * @brief Entità fuel che ripristica un certa quantià di carburante e di vita al giocatore
 * quando è colpita dal suo raggio
 */
class Fuel : public Entity{
	protected:
	double healthSize; // Punti salute che il giocatore guadagna quando colpisce il fuel con il raggio traente.
	double fuelSize; // punti carburante guadagnati
	public:
	/**
	 * @brief Costruttore di un carburante
	 * 
	 * @param world 
	 * @param origin 
	 */
	Fuel( Level *world, Point2D origin );

	/**
	 * @brief Callback che gestisce il comportamento di ripristino di una certa quantità
	 * di vita e carburante al giocatore se l'entità con cui ha colliso è il suo raggio
	 * 
	 * @param game 
	 * @param collide_ent 
	 */
	virtual void Callback_OnCollide( GameEngine *game, Entity *collide_ent );
};