#include "SolarSystem.hpp"
#include "engine/GameEngine.hpp"
#include "PlanetEntity.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <cmath>

SolarSystem::SolarSystem( Vector _bounds, unsigned int number_of_planets ) : Level( _bounds, "SolarSystem"){
	// il primo pianeta lo genero sempre in mezzo
	unsigned int MaxHeight = this->GetMaxHeight();
	unsigned int MaxWidth = this->GetMaxWidth();
	
	Point2D planet_origin = Point2D( 0, MaxHeight/2.0 );
	Vector offset_distance = Vector( planet_origin.GetSize() );
	Vector planet_bounds = Vector( planet_origin.GetSize() );
	for( unsigned int i = 0; i < number_of_planets; i++ ){
		unsigned int circumference = MaxWidth + (rand() % MaxWidth ); // TEMP
		unsigned int radius = 4 + circumference % 4;
		planet_bounds.Set( BOUND_INDEX_WIDTH, circumference );
		planet_bounds.Set( BOUND_INDEX_HEIGHT, MaxHeight );
		PlanetEntity *planet = new PlanetEntity( this, planet_origin, NULL, radius, planet_bounds );
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
			// dirigi il giocatore verso il centro del sistema solare ( questo creerebbe una specie di animazione )
			// quando arriva al centro: setto questo livello come garbage
			Point2D center_off_solar_system = Point2D( this->GetMaxWidth() / 2.0, this->GetMaxHeight() / 2.0 );
			double radius = 2;
			Vector level_bounds = this->GetBounds();
			if( this->player->GetOrigin().DistanceSquared( center_off_solar_system, &level_bounds ) <= (radius*radius) ){ // il giocatore di trova in un raggi di radius unità dal centro
				// aggiustio le sue coordinate, arrotondandole (per semplicità ma potrei anche non farlo)
				center_off_solar_system = this->player->GetOrigin();
				center_off_solar_system.round();
				this->player->SetOrigin( center_off_solar_system );
				// faccio notare all'engine che deve cambiare livello
				this->player->SetMoveOverride( NULL );
				this->GetOutPlayer();
				this->Delete( game );
				game->SetCurrentLevel( NULL );
				update_result = false;
			}
			else{
				// crea la direzione in cui muovere il giocatore
				Vector *direction = new Vector( this->player->GetOrigin().GetSize() );
				Vector _bounds = this->GetBounds();
				*direction = BuildDirection( this->player->GetOrigin(), center_off_solar_system, &_bounds );
				direction->Normalize(); // la normalizzo per farla diventare di lunghezza = 1
				// forzo lo spostamento del giocatore in questa direzione
				this->player->SetMoveOverride( direction );
			}
		}
		planet_entities.clear();
	}
	return update_result;
}

bool SolarSystem::IsGenerated(){
	return !this->entities.empty();
}