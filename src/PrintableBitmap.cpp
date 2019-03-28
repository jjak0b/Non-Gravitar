#include "PrintableBitmap.hpp"
#include <iostream>
PrintableBitmap::PrintableBitmap( unsigned int _rows, unsigned int _columns ) : Bitmap( _rows, _columns + 1){
	this->rows = _rows;
	this->columns = _columns;
	unsigned int size = (_rows * (_columns+1) );// il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima
/*
	this->data = new char[ size ];
	for( unsigned int i = 0; i < _rows; i++ ){
		for( unsigned int j = 0; j < _columns; j++ ){
			this->data[ (this->rows*i) + j ] =  (char)('0' + (j % ('9'+1 - '0') ));//BITMAP_DATA_EMPTY;
		}
	}*/
	for (unsigned int i = 0; i < size; i += 1) {
		
		this->data[ i ] =  (char)('0' + (i % ('9'+1 - '0') ));//BITMAP_DATA_EMPTY;
	}
}

char* PrintableBitmap::toString(){
	// utilizzo la +1-esima colonna di ogni riga con un '\n' e un '\0' alla fine del vettore
	unsigned int total_columns = this->columns * this->rows;
	for( unsigned int i = this->columns; i < total_columns; i += this->columns ){
		this->data[ i ] = '\n';
	}


	
	/*for( unsigned int i = 0; i < this->rows; i++ ){
		this->data[ ( ( this->rows * i ) + this->columns ) ] = '\n';
	}*/

	this->data[ total_columns ] = '\0';
	
	return this->data;
}