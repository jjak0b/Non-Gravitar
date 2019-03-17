#include "Bitmap.hpp"
#include <stddef.h>

Bitmap::Bitmap(unsigned int _rows, unsigned int _columns ){
	this->rows = _rows;
	this->columns = _columns;
	// char *data = new char[((width + 1) * height)]; // il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima
	unsigned int size = (_rows * _columns );
	if( size > 0){
		this->data = new char[ size ];
		for (unsigned int i = 0; i < size; i += 1) {
			this->data[ i ] = BITMAP_DATA_EMPTY;
		}
	}
}

unsigned int Bitmap::GetRows(){
	return this->rows;
}

unsigned int Bitmap::GetColumns(){
	return this->columns-1;
}

bool Bitmap::SetValue( BITMAP_DATA_TYPE value, unsigned int row, unsigned int column ){
	if( ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
		this->data[ ( ( this->rows * row ) + column ) ] = value;
		return true;
	}
	else{
		return false;
	}
}

BITMAP_DATA_TYPE Bitmap::GetValue( unsigned int row, unsigned int column ){
	if( ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
		return this->data[ ( ( this->rows * row ) + column ) ];
	}
	else{
		return BITMAP_DATA_EMPTY;
	}
}

void Bitmap::Copy( Bitmap *_data, unsigned int row, unsigned int column ){
	if( _data != NULL){
		for (unsigned int i = 0; i < _data->rows && i < this->rows; i += 1){
			for (unsigned int j = 0; j < _data->columns && j < this->columns; j += 1){
				this->SetValue( _data->GetValue( i, j ), row+i, column+j );
			}
		}
	}
}
