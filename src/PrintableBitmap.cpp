#include "PrintableBitmap.hpp"
#include "GameEngine.hpp"
#include "GameConfig.h"
#include <cstring>
#include "Color.hpp"

PrintableBitmap::PrintableBitmap( unsigned int _rows, unsigned int _columns ) : Bitmap( _rows, _columns	){

	// il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima
	unsigned int size = ( _rows * (_columns + 1 ) );

#ifdef ENABLE_ANSI_IF_SUPPORTED
	if( OsSupportAnsiEscape() ){ // ottimizzo la memoria allocata dal buffer da stampare
		size = (_rows * ( ( _columns + 1) * NUMBER_OF_CHAR_DEDICATED_TO_ANSI ) );
	}
#endif

	this->buffer = new std::string();
	// alloco la dimensione del numero di caratteri necessario per rappresentare questo oggetto in una stringa
	this->buffer->reserve( size );

}

PrintableBitmap::~PrintableBitmap(){
	if( this->buffer != NULL){
		delete this->buffer;
	}
}

const char* PrintableBitmap::toString(){
	if( this->buffer == NULL ){
		return NULL;
	}
	this->buffer->clear();
	unsigned int _columns = this->GetColumns();
	unsigned int _rows = this->GetRows();
	BITMAP_DATA_TYPE value;
#ifdef ENABLE_ANSI_IF_SUPPORTED
	unsigned int size_buffer = ( _rows * (_columns + 1) ) + 1;
	Color color = COLOR_WHITE;
	Color previousColor = COLOR_TRANSPARENT; // tiene traccia dell'ultimo colore diverso
	const unsigned int size_ANSI_buffer = NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1;
	char str_ANSI_buffer[ size_ANSI_buffer ] = "";
#endif

	for( unsigned int i = 0; i <_rows; i++ ){
		for( unsigned int j = 0; j <_columns; j++ ){
			value = this->GetValue( i, j );
#ifdef ENABLE_ANSI_IF_SUPPORTED
			if( OsSupportAnsiEscape() ) {
				color = this->GetColor(i, j);
				// configura la nuova cpodifica del colore ANSI solo se è differente da quello precedente -> maggiori performance sul terminale
				if( !color.Equals( previousColor )
				// && ( color.GetAlpha() != previousColor.GetAlpha() )
				){
					color.toANSI(str_ANSI_buffer);
					this->buffer->append(str_ANSI_buffer);
				}
				previousColor = color;
			}
#endif
			this->buffer->append( 1, value );
		}
		// utilizzo la +1-esima colonna di ogni riga inserendoci un '\n' e un '\0' alla fine del vettore
		if( i != _rows - 1 ) {
			this->buffer->append(1, '\n');
		}
		else{
#ifdef ENABLE_ANSI_IF_SUPPORTED
			if( OsSupportAnsiEscape() ) {
				this->buffer->append("\x1b[0m"); // resetto le codifica ansi dal carattere successivo
			}
#endif
			this->buffer->append( 1, '\0' );
		}

	}

	return this->buffer->c_str();
}

