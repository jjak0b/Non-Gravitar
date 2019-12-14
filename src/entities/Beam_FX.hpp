#pragma once
#include "Entity.hpp"

/**
 * @brief Entità puramente grafica che l'insieme di essa
 * unita altre entità dello stesso tipo, costituiscono l'effetto di un raggio
 * 
 */
class Beam_FX : public Entity{
	protected:
	Beam_FX *next = NULL;

	public:
	Beam_FX( Level *world, Point2D origin );


	/**
	 * @brief Aggiunge un nuovo Beam_FX alla fine della lista.
	 * @param origin Origine del nuovo elemento.
	*/
	void addNext(Point2D origin);

	/** 	
	 * @brief Elimina la lista.
	 * @param game 
	*/
	virtual void Delete( GameEngine* game );
};