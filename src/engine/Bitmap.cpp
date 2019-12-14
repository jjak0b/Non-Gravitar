#include "Bitmap.hpp"
#include "GameConfig.h"
#include "GameEngine.hpp"
#include <cstring>

#define ColoredBitmapColumnToBitmapColumn( index_column ) ( NUMBER_OF_CHAR_DEDICATED_TO_ANSI + ( ( NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1) * (index_column) ) )

template class Matrix::Matrix< BITMAP_DATA_TYPE >;
template class Matrix::Matrix< Color >;

Bitmap::Bitmap( unsigned int _rows, unsigned int _columns, Color color ) : Matrix< BITMAP_DATA_TYPE >::Matrix( _rows, _columns ){

	this->colors = new Matrix< Color >( _rows, _columns );
#ifdef DEBUG
	for( unsigned int i = 0; i < _rows; i++ ){
		for( unsigned int j = 0; j < _columns; j++ ){
			this->SetColor( color, i, j );
			// this->SetColor( Color( rand() % 256, rand() % 256, rand() % 256 ), i, j );
		}
	}
#else
	if( this->colors != NULL ){
		this->colors->Fill( color );
	}
#endif
}

Bitmap::~Bitmap(){
	if( this->colors != NULL ){
		delete this->colors;
		this->colors = NULL;
	}
}

BITMAP_DATA_TYPE Bitmap::GetValue( unsigned int row, unsigned int column){
	BITMAP_DATA_TYPE value;
	if( Matrix<BITMAP_DATA_TYPE>::GetValue( &value, row, column ) ){
		return value;
	}
	else{
		return BITMAP_DATA_NULL;
	}
}

bool Bitmap::SetColor( Color color, unsigned int row, unsigned int column ){
	if( this->colors != NULL ){
		return this->colors->SetValue( color, row, column );
	}
	else{
		return false;
	}
}

Color Bitmap::GetColor( unsigned int row, unsigned int column ){
	Color value;
	if( this->colors != NULL && this->colors->GetValue( &value, row, column ) ){
		return value;
	}
	else{
		return COLOR_TRANSPARENT;
	}
}

bool Bitmap::Load( const BITMAP_DATA_TYPE **texture, const Color **color_table, unsigned int _rows, unsigned int _columns ){
	bool result = true;
	if( texture != NULL) {
		result = Matrix<BITMAP_DATA_TYPE>::Load( texture, _rows, _columns );
	}

	if( this->colors != NULL && color_table != NULL ){
		result = result && this->colors->Load( color_table, _rows, _columns );
	}
	return result;
}

void Bitmap::Copy( Bitmap *_data, unsigned int row, unsigned int column ){
	if( _data != NULL) {
		Matrix<BITMAP_DATA_TYPE>::Copy( _data, row, column );
		if( this->colors != NULL ) {
			this->colors->Copy(_data->colors, row, column);
		}
	}
	
}

void Bitmap::Clear(){
	this->Fill( BITMAP_DATA_EMPTY );
	if( this->colors != NULL ){
		this->colors->Fill(COLOR_TRANSPARENT);
	}
}