#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"
#include <stdio.h>
#include <cstring>

#define ColoredBitmapColumnToBitmapColumn( index_column ) ( NUMBER_OF_CHAR_DEDICATED_TO_ANSI + ( ( NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1) * (index_column) ) )

ColoredBitmap::ColoredBitmap( unsigned int _rows, unsigned int _columns, Color color ) : Bitmap(
	_rows,
	(OsSupportAnsiEscape() ? (_columns * (NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1) ) : ( _columns ) ) ){ // allocazione di più o meno memoria se supportato o non
	if( OsSupportAnsiEscape() ){
		for( unsigned int i = 0; i < _rows; i++ ){
			for( unsigned int j = 0; j < _columns; j++ ){
				this->SetColor( color, i, j );
				// this->SetColor( Color( rand() % 256, rand() % 256, rand() % 256 ), i, j );
			}
		}
	}
}

unsigned int ColoredBitmap::GetColumns(){
	if( OsSupportAnsiEscape() ){
		return (this->realColumns / (NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1)) - ((this->realColumns - Bitmap::GetColumns()) / (NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1));
	}
	else{
		return Bitmap::GetColumns();
	}
}

void ColoredBitmap::SetSignificantColumns( unsigned int _columns ){
	if( OsSupportAnsiEscape() ){
		Bitmap::SetSignificantColumns( _columns * (NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1) );
	}
	else{
		Bitmap::SetSignificantColumns( _columns );
	}
}

bool ColoredBitmap::SetValue( BITMAP_DATA_TYPE value, unsigned int row, unsigned int column ){
	if( OsSupportAnsiEscape() ){
		return Bitmap::SetValue( value, row, ColoredBitmapColumnToBitmapColumn( column ) );
	}
	else{
		return Bitmap::SetValue( value, row, column );
	}
	
}

BITMAP_DATA_TYPE ColoredBitmap::GetValue( unsigned int row, unsigned int column ){
	if( OsSupportAnsiEscape() ){
		return Bitmap::GetValue( row, ColoredBitmapColumnToBitmapColumn( column )  );
	}
	else{
		return Bitmap::GetValue( row, column );
	}
}

bool ColoredBitmap::SetColor( Color color, unsigned int row, unsigned int column ){
	if( OsSupportAnsiEscape() ){
		const unsigned int size_str_ansi_color = NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1;
		const unsigned int lenght_str_ansi_color = NUMBER_OF_CHAR_DEDICATED_TO_ANSI;

		char str_ansi_color[size_str_ansi_color] = ""; // "\e[38;2;255;255;255m" è la stringa massima
		color.toANSI( str_ansi_color );
		unsigned int _column = 0;
		unsigned int _column_start = (column * (NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1) );
		for( unsigned int i = 0; i < lenght_str_ansi_color; i++ ){
			_column = _column_start + i;
			this->Bitmap::SetValue( str_ansi_color[i], row, _column );
		}
		return true;
	}
	else{
		return false;
	}
}

Color ColoredBitmap::GetColor( unsigned int row, unsigned int column ){
	if( OsSupportAnsiEscape() ){
		// TODO: finire implementazione ...
		return COLOR_BLUE;
		// Bitmap::GetValue( row, (column * COLUMNS_MOLT_USING_ANSI_COLORS) );
	}
	else{
		return Color( 255, 255, 255 );
	}
}

bool ColoredBitmap::Load( const BITMAP_DATA_TYPE **texture, const Color **color_table, unsigned int _rows, unsigned int _columns ){
	if( OsSupportAnsiEscape() ){
		if( texture != NULL ){
			_rows = this->GetRows();
			_columns = this->GetColumns();
			for( unsigned int i = 0; i < _rows; i++ ){
				for( unsigned int j = 0; j < _columns; j++ ){
					this->SetValue( texture[ i ][ j ], i, j );
					if( color_table != NULL ){
						this->SetColor( color_table[ i ][ j ], i, j);
					}
				}
			}
			return true;
		}
		return false;
	}
	else{
		return Bitmap::Load( texture, _rows, _columns );
	}
}

void ColoredBitmap::Copy( ColoredBitmap *_data, unsigned int row, unsigned int column ){
	if( OsSupportAnsiEscape() ){
		if( _data != NULL){
			unsigned int _rows = this->GetRows();
			unsigned int _columns = this->GetColumns();
			unsigned int _data_rows = _data->GetRows();
			unsigned int _data_columns = _data->GetColumns();
			for (unsigned int i = 0; i < _data_rows && i < _rows; i += 1){
				for (unsigned int j = 0; j < _data_columns && j < _columns; j += 1){
					this->SetValue( _data->GetValue( i, j ), row+i, column+j );
					this->GetColor( row+i, column+j );
				}
			}
		}
	}
	else{
		this->Bitmap::Copy( _data, row, column );
	}
	
}

void ColoredBitmap::Clear(){
	if( OsSupportAnsiEscape() ){
		unsigned int _columns = this->GetColumns();
		unsigned int _rows = this->GetRows();
		Color color = COLOR_WHITE;
		for (unsigned int i = 0; i < _rows; i += 1){
			for (unsigned int j = 0; j < _columns; j += 1){
				this->SetValue( BITMAP_DATA_EMPTY, i, j );// considero come se fosse trasparente
				this->SetColor( color, i, j );
			}
		}
	}
	else{
		Bitmap::Clear();
	}
}