#include "Color.hpp"
#include <stdio.h>

Color::Color( COLOR_COMPONENT_TYPE red, COLOR_COMPONENT_TYPE green, COLOR_COMPONENT_TYPE blue, COLOR_COMPONENT_TYPE alpha ){
	SetRed( red );
	SetGreen( green );
	SetBlue( blue );
	SetAlpha( alpha );
}

void Color::SetRed( COLOR_COMPONENT_TYPE value ){
	this->r = value;
}

COLOR_COMPONENT_TYPE Color::Color::GetRed(){
	return this->r;
}

void Color::SetGreen( COLOR_COMPONENT_TYPE value ){
	this->g = value;
}

COLOR_COMPONENT_TYPE Color::GetGreen(){
	return this->g;
}

void Color::SetBlue( COLOR_COMPONENT_TYPE value ){
	this->b = value;
}

COLOR_COMPONENT_TYPE Color::GetBlue(){
	return this->b;
}

void Color::SetAlpha( COLOR_COMPONENT_TYPE value ){
	this->a = value;
}

COLOR_COMPONENT_TYPE Color::GetAlpha(){
	return this->a;
}

bool Color::Equals( const Color color ){
	return r == color.r && g == color.g && b == color.b && a == color.a;
}

void Color::toANSI( char str_ansi_color[] ){
	const unsigned int size_str_ansi_color = NUMBER_OF_CHAR_DEDICATED_TO_ANSI+1;
	// "\e[38;2;255;255;255m" è la stringa massima
	// %03d indica che il massimo dumero ci cifre è 3, quindi riempie con zeri extra all'inizio del valori se < 3
	if( GetAlpha() < 255 ){
		snprintf( str_ansi_color, size_str_ansi_color, "\x1b[0m" );
	}
	else{
		snprintf( str_ansi_color, size_str_ansi_color, "\x1b[38;2;%03d;%03d;%03dm", this->GetRed(), this->GetGreen(), this->GetBlue() );
	}
}
