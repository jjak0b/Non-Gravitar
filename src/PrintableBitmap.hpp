#pragma once

#include "Bitmap.hpp"

class PrintableBitmap : public Bitmap{
public:
	PrintableBitmap( unsigned int _rows, unsigned int _columns ){
		this->rows = _rows;
		this->columns = _columns;
		unsigned int size = (_rows * (_columns+1) );// il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima
		this->data = new char[ size ];
		for (unsigned int i = 0; i < size; i += 1) {
			this->data[ i ] = BITMAP_DATA_EMPTY;
		}
	}

	char* toString();
};