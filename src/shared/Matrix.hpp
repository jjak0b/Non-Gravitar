#pragma once

namespace Matrix {
	template < class T >
	class Matrix {
	protected:
		unsigned int realRows, realColumns; // righe e colonne allocate alla Matrix
		unsigned int rows, columns; // righe e colonne significative del Matrix
		T* data; // vettore contenente i valori che rappresentano questa matrice ( vettore di dimensione righe*colonne)

	public:
		Matrix(unsigned int _rows = 0, unsigned int _columns = 0 );

		virtual ~Matrix();

		/**
		 * @Brief Assegna af ogni elemento di questo oggetto del valore specificato
		 * @param value
		 */
		void Fill( const T value );

		/**
		 * @Brief Copia un array di 2 dimensioni in questo oggetto
		 * @param array2d
		 * @param rows
		 * @param columns
		 * @return true se l'operazione è andata a buon fine, false altrimenti
		 */
		bool Load( const T **array2d, unsigned int rows, unsigned int columns );

		/**
		 * @return Il numero di righe significative di questo oggetto
		 */
		unsigned int GetRows();

		/**
		 * @return Il numero di colonne significative di questo oggetto
		 */
		unsigned int GetColumns();

		/**
		 * @brief Imposta il dato da inserira nella row-esima riga e column-esima colonna
		 *
		 * @param value il dato da inserire
		 * @param row
		 * @param column
		 * @return true se il dato è stato inserito nella Bitmap
		 * @return false altrimenti
		 */
		bool SetValue( const T value, unsigned int row, unsigned int column );

		/**
		 * @brief Restituisce il dato della row-esima riga e column-esima colonna, e lo assegna al valore punatato da value
		 * @PreCondition: value != NULL
		 * @param value
		 * @param row
		 * @param column
		 * @return true se il valore è stato assegnato, false altrimenti
		 */
		bool GetValue( T* value, unsigned int row, unsigned int column );

		/**
		 * @brief Copia il bitmap fornito in questo bitmap a partire dalla row-esima riga e column-esima colonna.
		 * Non verranno copiati i dati negli indici che superano this->rows o this->columns
		 *
		 * @param _data puntatore del bitmap da copiare
		 * @param row
		 * @param column
		 */
		void Copy( Matrix *_data, unsigned int row, unsigned int column );

	protected:
		/**
		 * @brief Imposta il numero di righe significative di questo oggetto;
		 * @PostCondition: Quindi le future operazioni su questo oggetto modificheranno o leggeranno in base a questo numero impostato
		 * @param _rows
		 */
		void SetSignificantRows( unsigned int _rows );

		/**
		 * @brief Imposta il numero di colonne significative di questo oggetto
		 * @PostCondition: Quindi le future operazioni su questo oggetto modificheranno o leggeranno in base a questo numero impostato
		 * @param _columns
		 */
		void SetSignificantColumns( unsigned int _columns );
	};
}

#include "Matrix.cpp" // inclusione particolare: unisco interfaccia e implementazione del templete

