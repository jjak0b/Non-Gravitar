#pragma once

#include "Bitmap.hpp"
#include <string>

class PrintableBitmap : public Bitmap{
protected:
	std::string* buffer;
public:
	PrintableBitmap( unsigned int _rows = 0, unsigned int _columns = 0);

	virtual ~PrintableBitmap();

	/**
	 * @brief Restituisce un puntatore ad una stringa C codificata in sequenze ESCAPE ANSI
	 * contenente i caratteri e i colori della Bitmap, affinchè se stampa su terminale,
	 * siano mostrati i caratteri con il colore assegnato
	 * @PostCOndition il puntatore non deve essere deallocato perchè il buffer fa parte di questo oggetto
	 * @return const char* 
	 */
	const char* toString();
};