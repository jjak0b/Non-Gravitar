#include "PlanetLevel.hpp"
#include "PlanetEntity.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

PlanetLevel::PlanetLevel( PlanetEntity *planet_entity, unsigned int max_longitude, unsigned int max_altitude ) : Level( max_longitude, max_altitude, "PlanetLevel"){
	this->planet_entity = planet_entity;
}

PlanetEntity *PlanetLevel::GetPlanetEntity(){
	return this->planet_entity;
}

bool PlanetLevel::Update( GameEngine *game ){
	bool update_result = Level::Update( game );
	if( update_result ){
		if( IsDefined( this->GetPlayer() ) && this->GetPlayer()->IsOutOfTheWorld() ){
			game->SetCurrentLevel( this->GetPlanetEntity()->GetWorld() ); // carica il sistema solare come prossimo livello del successivo Update
			game->GetCurrentLevel()->AddEntity( this->GetOutPlayer() );
			
			if( this->IsFree() ){
				this->garbage = true;
				this->Delete( false );
			}

			update_result = false;
		}
	}

	return update_result;
}

bool PlanetLevel::IsFree(){
	list<Entity*> bunkers = this->GetEntities("Bunker", false, true );
	bool isFree = bunkers.empty();
	bunkers.clear();
	return isFree;
}
