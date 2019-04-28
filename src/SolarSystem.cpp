#include "SolarSystem.hpp"
#include "Level.hpp"
#include "Planet.hpp"
#include "Player.hpp"
#include <time.h>
#include <cstdlib>
#include <cmath>

SolarSystem::SolarSystem( unsigned int MaxWidth, unsigned int MaxHeight, unsigned int number_of_planets, Player *_player ) : Level( NULL, MaxWidth, MaxHeight, "SolarSystem", _player ){
	this->player->SetOrigin( Point2D( MaxWidth/2.0, MaxHeight/2.0 ) );
	
	// il primo pianeta lo genero sempre in mezzo
	Point2D planet_origin = Point2D( 0, MaxHeight/2.0 );
	Vector offset_distance = Vector( planet_origin.GetSize() );
	for( unsigned int i = 0; i < number_of_planets; i++ ){
		Planet *p = new Planet( this, planet_origin, MaxWidth );
		// imposta l'offset di posizione (del prossimo pianeta) dalla posizione del pianeta generato in precedenza
		offset_distance.Reset();
		if( MaxHeight != 0 ){
			offset_distance.Set( 1, rand() % (int)(MaxHeight/2.0) ); // l'offset y sarà casuale da 0 + o - (MaxHeight/2.0)-1 
		}
		else{
			offset_distance.Set( 1, 0 );
		}
		offset_distance.Scale( pow( -1, rand() % 2 ) );
		offset_distance.Set( 0, MaxWidth / number_of_planets );
		planet_origin.Add( offset_distance );
		planet_origin = this->GetNormalizedPoint( planet_origin );
	}
}