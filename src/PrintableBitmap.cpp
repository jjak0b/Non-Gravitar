#include "PrintableBitmap.hpp"
#include "GameConfig.h"

PrintableBitmap::PrintableBitmap( unsigned int _rows, unsigned int _columns ) : ColoredBitmap( _rows, _columns + 1){ // il +1 è usato per aggiungere \n ad ogni riga, e \0 nell'ultima	
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
		this->SetValue( '\n' , i, _columns ); // this->data[ ( (this->realColumns ) * i) + (this->columns) ] = '\n';
	}

	this->SetValue( '\0' , _rows-1, _columns ); // this->data[ size ] = '\0';

	// Una bitmap di dimensione _rows * (_columns + 1) è stata istanziata,
	// ma voglio che possa accedere solo alle celle significative, quindi imposto le righe e colonna di una normale bitmap
	this->SetSignificantColumns( _columns ); // rendo inaccessibile esternamente l'ultima colonna
}

char* PrintableBitmap::toString(){
	
	unsigned int _columns = this->GetColumns();
	unsigned int _rows = this->GetRows();
	this->SetSignificantColumns( _columns + 1 );
	for( unsigned int i = 0; i <_rows; i++ ){
		// utilizzo la +1-esima colonna di ogni riga inserendoci un '\n' e un '\0' alla fine del vettore
		this->SetValue( '\n' , i, _columns); // this->data[ ( (this->realColumns) * i) + (this->columns) ] = '\n';
	}
	this->SetValue( '\0' , _rows-1, _columns ); // this->data[ this->realRows*this->realColumns ] = '\0';
	this->SetSignificantColumns( _columns );
	return this->data;
}

