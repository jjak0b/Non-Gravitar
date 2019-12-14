#pragma once

#include "engine/GameConfig.h"
#include "Point2D.hpp"
#include <stddef.h>

class Vector;
#ifdef DEBUG_COLLISION_DRAWING
class GameEngine;
#endif
class Segment {
protected:
	Point2D start; // punto iniziale del segmento
	Point2D end; // punto finale del segmento
	bool isVertical; // indica se il segmento appartiene ad una retta verticale
	bool isHorizontal; // indica se il segmento appartiene ad una retta orizzontale
	VECTOR_VALUE_TYPE m; // coefficiente angolare della retta a cui il segmento appartiene
	VECTOR_VALUE_TYPE q; // ordinata all'origine

public:

	Segment(Point2D start = Point2D(), Point2D end = Point2D(), Vector* bounds = NULL );

	Point2D GetStart();

	Point2D GetEnd();

	/**
	 * @brief restituisce il coefficiente angolare della retta, assegnandolo a value
	 * @PreCondition: value != NULL
	 * @param value
	 * 
	 * @return true se a value è stato assegnato un valore
	 * @return false altrimenti, cioè la retta è verticale
	 */
	bool GetM( VECTOR_VALUE_TYPE* value );

	/**
	 * @brief restituisce il valore dell'ordinata all'origine, assegnandolo a value
	 * @PreCondition: value != NULL
	 * @param value 
	 * @return true se a value è stato assegnato un valore -> la retta non è verticale
	 * @return false altrimenti -> M è nullo quindi la retta à verticale
	 */
	bool GetQ( VECTOR_VALUE_TYPE* value );

	/**
	 * @brief Indica se la retta è verticale in base al suo coefficiente angolare
	 * 
	 * @return true 
	 * @return false 
	 */
	bool IsVertical();

	/**
	 * @brief Indica se la retta è orizzontale in base al suo coefficiente angolare
	 *
	 * @return true
	 * @return false
	 */
	bool IsHorizontal();

	/**
	 * @brief Indica se la retta interseca line
	 * 
	 * @param segment
	 * @return true 
	 * @return false 
	 */
	bool IsIntersecting(
#ifdef DEBUG_COLLISION_DRAWING
							GameEngine* game,
#endif
							Segment segment );

protected:

	/**
	 *	@brief Calcola il coefficiente angolare e l'ordinata all'origine in base ai limiti degli assi in bounds, e assegnando il corretto valore a IsVertical
	 * 
	 * @param bounds 
	 */
	void evaluate( Vector* bounds );

};