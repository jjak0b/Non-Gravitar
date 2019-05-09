#include "SolarSystem.hpp"
#include "GameEngine.hpp"
#include "PlanetEntity.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <cmath>

SolarSystem::SolarSystem( unsigned int MaxWidth, unsigned int MaxHeight, unsigned int number_of_planets ) : Level( MaxWidth, MaxHeight, "SolarSystem"){
	// il primo pianeta lo genero sempre in mezzo
	Point2D planet_origin = Point2D( 0, MaxHeight/2.0 );
	Vector offset_distance = Vector( planet_origin.GetSize() );
	for( unsigned int i = 0; i < number_of_planets; i++ ){
		unsigned int circumference = MaxWidth + (rand() % MaxWidth ); // TEMP
		unsigned int radius = 4 + circumference % 4;
		PlanetEntity *planet = new PlanetEntity( this, planet_origin, NULL, radius, circumference, MaxHeight );
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

bool SolarSystem::Update( GameEngine *game ){
	bool update_result = Level::Update( game );
	if( update_result ){
		list<Entity*> planet_entities = this->GetEntities( "Planet", false, true );
		if( planet_entities.empty() ){
			Player *player = this->GetPlayer();
			// dirigi il giocatore verso il centro del sistema solare ( questo creerebbe una specie di animazione )
			// quando arriva al centro: setto questo livello come garbage
			Point2D center_off_solar_system = Point2D( this->GetMaxWidth() / 2.0, this->GetMaxHeight() / 2.0 );
			if( player->GetOrigin().Equals( center_off_solar_system ) ){
				game->SetCurrentLevel( NULL );
				this->garbage = true;
				update_result = false;
			}
			else{
				// direzione = punto fine - punto inizio
				Vector direction = player->GetOrigin();
				direction.Scale( -1.0 );
				direction.Add( center_off_solar_system );

				player->SetOrigin( player->GetOrigin().Add( direction ) ); // la posizione sarà normalizzata quando l'update del player sarà eseguito
			}
		}
	}
	return update_result;
}

bool SolarSystem::IsGenerated(){
	return !this->entities.empty();
}