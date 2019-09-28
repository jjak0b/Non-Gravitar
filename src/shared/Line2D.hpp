#pragma once

#include "Side.hpp"

class Vector;

class Line2D : public Side {
protected:
	bool isVertical;
	VECTOR_VALUE_TYPE m; // coefficiente angolare
	VECTOR_VALUE_TYPE q; // ordinata all'origine

public:

	Line2D( Side segment, Vector* bounds );

	/**
	 * @brief restituisce il coefficiente angolare della retta, assegnandolo a value
	 * @PreCondition: value != NULL
	 * @param value 
	 * @return true se a value è stato assegnato un valore -> la retta non è verticale
	 * @return false altrimenti -> M è nullo quindi la retta à verticale
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
	 * @brief Indica se la retta interseca line
	 * 
	 * @param line 
	 * @return true 
	 * @return false 
	 */
	bool IsIntersecting( Line2D line );

protected:

	/**
	 *	@brief Calcola il coefficiente angolare e l'ordinata all'origine in base ai limiti degli assi in bounds, e assegnando il corretto valore a IsVertical
	 * 
	 * @param bounds 
	 */
	void evaluate( Vector* bounds );

};