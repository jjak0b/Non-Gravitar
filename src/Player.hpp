#pragma once

#include "DamageableEntity.hpp"
#include "Point2D.hpp"
#include "GameConfig.h"

class GameEngine;
class Level;
class Projectile;

class Player : public DamageableEntity{
	protected:
	INPUT_TYPE lastInput; // l'ultimo input ricevuto
	Vector lastMove; // l'ultimo spostamento effettuato
	Vector *moveOverride; // spostamento obbligato dal gioco
	public:
	Player( Level *world, Point2D origin, double health );
	bool Update( GameEngine *game );
	void Draw( ViewPort *view );
	void Delete();
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

	/**
	 * @brief Imposta il movimento che il giocatore deve compiere forzatamente durante l'update succesivo di questa entità alla chiamata di questo metodo.
	 * Impostare direction = NULL se si vuole annullare il movimento forzato, altrimenti esso viene mantenuto ad ogni Update
	 * PreCondition: la dimensione del vettore direzione deve essere la stessa del punto posizione ( origin )
	 * PostCondition: Se un moveOverride è stato già precedentemente impostato, esso viene deallocato e sostituito con questo.
	 * @param direction 
	 */
	void SetMoveOverride( Vector *direction );
};
