#include "Bitmap.hpp"
#include <stddef.h>
#include <iostream>

Bitmap::Bitmap(unsigned int _rows, unsigned int _columns ){
	this->realRows = _rows;
	this->realColumns = _columns;
	this->rows = _rows;
	this->columns = _columns;
	unsigned int size = (_rows * _columns );
	if( size > 0){
		this->data = new char[ size ];
		this->Clear();
	}
}

void Bitmap::SetSignificantRows( unsigned int _rows ){
	this->rows = _rows < this->realRows ? _rows : this->realRows;
}

void Bitmap::SetSignificantColumns( unsigned int _columns ){
	this->columns = _columns < this->realColumns ? _columns : this->realColumns;
}

unsigned int Bitmap::GetRows(){
	return this->rows;
}

unsigned int Bitmap::GetColumns(){
	return this->columns;
}
bool Bitmap::Load( const BITMAP_DATA_TYPE **texture, unsigned int _rows, unsigned int _columns ){
	if( texture != NULL ){
		unsigned int min_rows = _rows > this->rows ? this->rows : _rows;
		unsigned int min_columns = _columns > this->columns ? this->columns : _columns;
		for( unsigned int i = 0; i < min_rows; i++ ){
			for( unsigned int j = 0; j < min_columns; j++ ){
				this->SetValue( texture[ i ][ j ], i, j );
			}
		}
	}
}

bool Bitmap::SetValue( BITMAP_DATA_TYPE value, unsigned int row, unsigned int column ){
	if( ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
		this->data[ ( ( this->realColumns * row ) + column ) ] = value;
		return true;
	}
	else{
		return false;
	}
}

BITMAP_DATA_TYPE Bitmap::GetValue( unsigned int row, unsigned int column ){
	if( ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
		return this->data[ ( ( this->realColumns * row ) + column ) ];
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

void Bitmap::Dispose(){
	delete this->data;
	this->data = NULL;
	this->realRows = 0;	
	this->realColumns = 0;
	this->rows = 0;
	this->columns = 0;
}

void Bitmap::Clear(){
	for (unsigned int i = 0; i < this->rows; i += 1){
		for (unsigned int j = 0; j < this->columns; j += 1){
			this->data[ ( ( this->realColumns * i ) + j ) ] = BITMAP_DATA_EMPTY; // considero come se fosse trasparente
		}
	}
}