#include "SolarSystem.hpp"
#include "engine/GameEngine.hpp"
#include "PlanetEntity.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <cmath>
#include "shared/Utility.h"
SolarSystem::SolarSystem( Vector _bounds, unsigned int number_of_planets ) : Level( _bounds, "SolarSystem"){
    this->count_planets = number_of_planets;
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

void SolarSystem::Generate(GameEngine *game) {
    // il primo pianeta lo genero sempre in mezzo
    unsigned int MaxHeight = this->GetMaxHeight();
    unsigned int MaxWidth = this->GetMaxWidth();

    Point2D ent_origin = Point2D( 0, MaxHeight/2.0 );;
    unsigned int last_radius = 10;
    if( GetPlayer() != NULL ){
        ent_origin = GetPlayer()->GetOrigin();
    }

    Point2D planet_origin = ent_origin; // faccio finta che il pianeta precedente è stato generato nella poszione del pianeta
    Vector planet_bounds = Vector( planet_origin.GetSize() );
    Vector offset_distance = Vector( planet_origin.GetSize() );
    double scale = 1.0; // fattore di inversione dell'offset Y
    VECTOR_VALUE_TYPE offset; // distanza di variazione in una singola componente
    for( unsigned int i = 0; i < count_planets; i++ ){
        unsigned int circumference = MaxWidth + (rand() % MaxWidth ); // TEMP
        unsigned int radius = 4 + circumference % 5;
        planet_bounds.Set( BOUND_INDEX_WIDTH, circumference );
        planet_bounds.Set( BOUND_INDEX_HEIGHT, MaxHeight );
        PlanetEntity *planet = NULL;

        // evito che il pianeta venga generato dove si trova il giocatore o lo scorso pianeta !!!

        // parto dalla metà del piano in asse Y e poi aggiunto un certo offset Y di spostamento
        planet_origin.SetY( MaxHeight/2.0 );

        if( MaxHeight != 0 ){
            offset = RANDOM_RANGE( 0, MaxHeight / 2.0 ) ;
        }
        else{
            offset = 0;
        }
        offset *= scale; // vario l'offset in Y in modo alternato
        offset_distance.Set( BOUND_INDEX_HEIGHT, offset );

        // dall'origine precedente lascio lo spazio minimo richiesto:
        // spazio del raggio precedente + raggio attuale
        // oltre alla distanza minima, aggiungo una distanza aggiuntiva randomizzata
        // la distanza aggiuntiva è bilanciata per un valore massimo per cui non possono sovraporsi pianeti
        offset = RANDOM_RANGE( (last_radius + radius), (MaxWidth / (count_planets)) );
        offset_distance.Set( BOUND_INDEX_WIDTH, offset );

        // aggiungo l'offset calcolato all'origine precedente
        planet_origin.Add( offset_distance );

        // Il costruttore di Entity Aggiunge in automatico l'entità al mondo
        planet = new PlanetEntity(this, planet_origin, NULL, radius, planet_bounds);

        last_radius = radius;
        scale *= -1.0; // cambio il fattore di inversione dell'offset Y
    }
}
bool SolarSystem::IsGenerated(){
	return !this->entities.empty();
}