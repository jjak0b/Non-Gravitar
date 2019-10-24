#pragma once
#include "Entity.hpp"

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