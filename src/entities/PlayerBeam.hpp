#pragma once

#include "Projectile.hpp"
#include "Beam_FX.hpp"

/**
 * @brief Entità proiettile che implementa il comportamento grafico di un raggio
 * 
 */
class PlayerBeam : public Projectile{
	protected:
	Beam_FX *fx;	// lista di entità che costituisce la Texture del raggio durante l'esecuzione
	public:

	PlayerBeam( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed );

	/**
	 * @brief Aggiorna lo stato di questa entità
	 * Poichè ad ogni update si trova ad una posizione diversa,
	 * genera ad ogni Update un entità Beam_FX che ha il solo scopo di mostrare sulla ViewPort
	 * un effetto di una texture animata nel tempo
	 * @param game 
	 * @return true 
	 * @return false 
	 */
	virtual bool Update( GameEngine *game );
};