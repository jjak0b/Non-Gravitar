//
// Created by Jacopo on 20/09/2019.
//

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include "Point2D.hpp"
#include <list>

#define RANDOM_RANGE( min, max ) ( (min) + (rand() % (int)( (max) - (min) )))
#define SQR( value ) ( (value)*(value) )
#define ISINRANGE(min, value, max ) ( (min) <= (value) && (value) <= (max) )
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

namespace Utility {
	
	template < class T >
	struct range_t {
		T min;
		T max;
		T value;
	};
	
	/**
	* @Brief Verifica se una stringa combacia con una seconda stringa, o contiene una sottostringa
	* @PreCondition str e str_or_substr devono essere stringhe C
	* @param str stringa principale
	* @param str_or_substr stringa da confrontare
	* @param check_as_subString true si se vuole controllare se str_or_substr sia strsottostringa di str
	* @return true se il confronto risulata positivo
	*/
	bool CheckEqualsOrSubstring(const char *str, const char *str_or_substr, bool check_as_subString);

	std::list<Point2D>::iterator random_element(std::list<Point2D>::iterator begin, std::list<Point2D>::iterator end);

	void sleep( unsigned milliseconds );

	namespace GUI {

		/**
		 * @brief Pulisce completamente il contenuto della finestra terminale
		 * 
		 */
		void ClearScreen();
		
		/**
		 * @Brief Wrapper di conio.h::_kbhit()
		 * per conoscere se è stato premuto un tasto
		 * @return true se è stato premuto un tasto
		 * @return false altrimenti
		 */
		bool IsKeyPressed();
		
		/**
		 * @Brief Wrapper di conio.h::_getch()
		 * per prendere un carattere di input
		 * @return il valore ASCII intero del carattere rivelato in input
		 */
		int GetKeyboardInput();

		namespace Terminal {

			/**
			 * @brief Imposta il cursore del terminale ad una poszione specifica
			 * Nota: (0,0) è in alto a sinistra del terminale
			 * 
			 * @param x 
			 * @param y 
			 */
			void SetTerminalCursor(int x, int y);

			/**
			 * @brief Restituisce le dimensioni della finistra in una tupla di un punto
			 * 
			 * @return Point2D 
			 */
			Point2D GetTerminalSize();
			
			/**
			 * @brief Indica se il sistema operativo supporta le funzionalità delle sequenze escape
			 * sul terminale
			 * Nota:
			 * su sistemi Unix è supportato,
			 * su sistemi Windows solo su versioni < Windows XP e >= Windows 10 Anniversary Update
			 * su altri sistemi non è supportato
			 * @PreCondition: Vedere Requisiti minimi su readme
			 * 
			 * @return true se supportato
			 * @return false altrimenti
			 */
			bool OsSupportAnsiEscape();

		}
	}
}

#endif
