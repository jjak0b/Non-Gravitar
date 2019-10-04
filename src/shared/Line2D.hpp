#pragma once

#include "Side.hpp"
#include <stddef.h>
class Vector;

class Line2D : public Side {
protected:
	bool isVertical;
	bool isHorizontal;
	VECTOR_VALUE_TYPE m; // coefficiente angolare
	VECTOR_VALUE_TYPE m_inverse; // (m)^-1 inversa del coefficiente angolare
	VECTOR_VALUE_TYPE q; // ordinata all'origine

public:

	Line2D( Side segment = Side(), Vector* bounds = NULL );

	/**
	 * @brief restituisce il coefficiente angolare della retta o il suo onverso, assegnandolo a value
	 * @PreCondition: value != NULL
	 * @param value
	 * @param inverse := se true assegnerà l'inversa del coefficiente angolare, altrimenti no
	 * @return true se a value è stato assegnato un valore
	 * 		-> se inverse = false la retta non è verticale
	 * 		-> se inverse = true la retta non è orizzontale
	 * @return false altrimenti -> M è nullo
	 * 		-> se inverse = false la retta à verticale
	 * 		-> se inverse = true la retta à orizzontale
	 */
	bool GetM( VECTOR_VALUE_TYPE* value, bool inverse );

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