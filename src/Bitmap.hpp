#pragma once

typedef char BITMAP_DATA_TYPE;
#define BITMAP_DATA_EMPTY ' '
#define BITMAP_DATA_NULL '\0'

class Bitmap{
	protected:
	unsigned int rows, columns; // righe e colonne del Bitmap
	BITMAP_DATA_TYPE *data; // vettore contenente i valori che rappresentano questa bitmap ( vettore di dimensione righe*colonne)

	public:
	Bitmap(unsigned int _rows = 0, unsigned int _columns = 0 );
	void Dispose(); // libera le risorse allocate su data
	bool load( BITMAP_DATA_TYPE **texture, unsigned int rows, unsigned int columns );
	unsigned int GetRows();
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
	bool SetValue( BITMAP_DATA_TYPE value, unsigned int row, unsigned int column );

	/**
	 * @brief restituisce il dato da della row-esima riga e column-esima colonna
	 * 
	 * @param row 
	 * @param column 
	 * @return BITMAP_DATA_TYPE 
	 */
	BITMAP_DATA_TYPE GetValue( unsigned int row, unsigned int column );

	/**
	 * @brief Copia il bitmap fornito in questo bitmap a partire dalla row-esima riga e column-esima colonna.
	 * Non verranno copiati i dati negli indici che superano this->rows o this->columns
	 * 
	 * @param _data puntatore del bitmap da copiare
	 * @param row 
	 * @param column 
	 */
	void Copy( Bitmap *_data, unsigned int row, unsigned int column );

	char* toString();

};