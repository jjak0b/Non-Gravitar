#include "PrintableBitmap.hpp"
#include "GameConfig.h"

PrintableBitmap::PrintableBitmap( unsigned int _rows, unsigned int _columns ) : Bitmap( _rows, _columns + 1){ // il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima
	// Una bitmap di dimensione _rows * (_columns + 1) è stata istanziata,
	// ma voglio che possa accedere solo alle celle significative, quindi imposto le righe e colonna di una normale bitmap
	this->SetSignificantColumns( _columns );
	unsigned int size = this->realColumns * this->realRows;
	
#ifdef DEBUG
	unsigned int c = 0;
#endif

	for( unsigned int i = 0; i < _rows; i++ ){
#ifdef DEBUG // In ogni colonna (esclusa la +1-esima) viene inserita una cifra da 0 a 9
		for( unsigned int j = 0; j < _columns; j++ ){
			this->SetValue( (char)('0' + (c % ('9'+1 - '0') ) ), i, j );
			c++;
		}
#endif
		// utilizzo la +1-esima colonna di ogni riga inserendoci un '\n' e un '\0' alla fine del vettore
		this->data[ ( (this->realColumns ) * i) + (this->columns) ] = '\n';
	}
	this->data[ size ] = '\0';
}

char* PrintableBitmap::toString(){
	for( unsigned int i = 0; i < this->rows; i++ ){
		// utilizzo la +1-esima colonna di ogni riga inserendoci un '\n' e un '\0' alla fine del vettore
		this->data[ ( (this->realColumns) * i) + (this->columns) ] = '\n';
	}
	this->data[ this->realRows*this->realColumns ] = '\0';
	return this->data;
}

