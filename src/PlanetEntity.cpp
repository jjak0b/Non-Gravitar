#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "GameEngine.hpp"
#include "SolarSystem.hpp"
#include "Player.hpp"
#include <cstring>

PlanetEntity::PlanetEntity( SolarSystem *world, Point2D origin, ColoredBitmap *texture, unsigned int _radius, unsigned int max_longitude, unsigned int max_altitude ) : Entity( world, origin, texture, "PlanetEntity" ){
	this->radius = _radius;
	this->planet_level = new PlanetLevel( this, max_longitude, max_altitude );
}

PlanetLevel *PlanetEntity::GetPlanetLevel(){
	return this->planet_level;
}

bool PlanetEntity::Update( GameEngine *game ){
	bool update_result = this->Entity::Update( game ); // Update Fondamentale

	if( update_result && IsDefined( this->GetPlanetLevel() ) ){
		// Mi interessa verificare solo la collisione con l'entità giocatore per verifica se vuole entrare nel pianeta
		Player *player = this->GetWorld()->GetPlayer();
		if( this->IsColliding( player ) ){
			this->Callback_OnCollide( game, player, player->GetOrigin() );
			update_result = false;
		}
	}
	else{
		this->Delete();
		update_result = false;
	}
	return update_result;
}

void PlanetEntity::Draw( ViewPort *view ){
	if( IsDefined( this ) )
		DrawCircle( view, this->world, this->origin, this->radius );
}

bool PlanetEntity::IsColliding( Entity *entity ){
	if( IsDefined(this) && IsDefined(entity) && this->GetOrigin().Distance( entity->GetOrigin() ) <= this->radius ){
		return true;
	}
	return false;
}

void PlanetEntity::Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin ){
	if( IsDefined( this ) && IsDefined( collide_ent ) ){
		if( !strcmp( collide_ent->GetClassname(), "Player" ) ){
			Player *player = (Player*)collide_ent;
			player = player->GetWorld()->GetOutPlayer();
			this->GetPlanetLevel()->AddEntity( player );
			game->SetCurrentLevel( this->GetPlanetLevel() );
		}
	}
}

void PlanetEntity::Delete(){
	if( this->planet_level != NULL ){
		this->planet_level->Delete( false );
		delete this->planet_level;
		this->planet_level = NULL;
	}
	this->Entity::Delete();
}
