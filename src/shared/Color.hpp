#pragma once

#define COLOR_COMPONENT_TYPE unsigned char

#define COLOR_RED Color( 255, 0, 0 )
#define COLOR_ORANGE Color( 255, 127, 0 )
#define COLOR_YELLOW Color( 255, 255, 0 )
#define COLOR_GREEN Color( 0, 255, 0 )
#define COLOR_BLUE Color( 0, 0, 255 )
#define COLOR_BLACK Color( 0, 0, 0 )
#define COLOR_GREY Color( 127, 127, 127 )
#define COLOR_WHITE Color( 255, 255, 255 )
#define COLOR_TRANSPARENT Color( 0, 0, 0, 0 )
#define NUMBER_OF_CHAR_DEDICATED_TO_ANSI 19

class Color{
	protected:
	COLOR_COMPONENT_TYPE r, g, b, a; // componenti colori red, green, blue, alpha in 2^8 = 256 valori (alpha 0 = transparente)

	public:

	Color( COLOR_COMPONENT_TYPE red = 0, COLOR_COMPONENT_TYPE green = 0, COLOR_COMPONENT_TYPE blue = 0, COLOR_COMPONENT_TYPE alpha = 255 );

	void SetRed( COLOR_COMPONENT_TYPE value );

	COLOR_COMPONENT_TYPE GetRed();

	void SetGreen( COLOR_COMPONENT_TYPE value );

	COLOR_COMPONENT_TYPE GetGreen();

	void SetBlue( COLOR_COMPONENT_TYPE value );

	COLOR_COMPONENT_TYPE GetBlue();

	void SetAlpha( COLOR_COMPONENT_TYPE value );

	COLOR_COMPONENT_TYPE GetAlpha();

	bool Equals( const Color color );

	/**
	 * @brief Copia nell'array fornito, una stringa contenente il formato Escape ANSI, del colore fornito.
	 *
	 * PreCondition: str_ansi_color deve essere di dimensione NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1
	 * PostCondition: la stringa fornita è del tipo "\x1b[38;2;255;255;255m", con i valori 255 sostituiti con i valori r g b rispettivamente di questo oggetto
	 * se alpha < 1 ignora le componenti del colore e resetta il colore di default (dipende dal terminale)
	 * @param color 
	 * @param str_ansi_color 
	 */
	void toANSI( char str_ansi_color[] );
};