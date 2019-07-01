#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "GameEngine.hpp"
#include "SolarSystem.hpp"
#include "Player.hpp"
#include <cstring>

PlanetEntity::PlanetEntity( SolarSystem *world, Point2D origin, ColoredBitmap *texture, unsigned int _radius, unsigned int max_longitude, unsigned int max_altitude ) : Entity( world, origin, texture, "PlanetEntity" ){
	this->radius = _radius;
	this->planet_level = new PlanetLevel( this, max_longitude, max_altitude );

	this->escape_point = this->GetOrigin(); // origine pianeta + offset di ( 0, this->radius + 1 )
	Vector default_escape_point_offset = Vector( this->escape_point.GetSize() );
	default_escape_point_offset.Set( 1, this->radius + 1 );
	this->escape_point.Add( default_escape_point_offset );
}

PlanetEntity::~PlanetEntity(){
	this->Delete(); // aggiungerà eventualmente il livello associato al garbage collector
}

void PlanetEntity::Delete(){
	if( !this->IsGarbage() ){
		if( IsDefined( this->planet_level ) ){
			this->planet_level->Delete(); // questo livello verrà aggiunto al garbage collector
			this->planet_level = NULL;
		}
		this->Entity::Delete();
	}
}

PlanetLevel *PlanetEntity::GetPlanetLevel(){
	return this->planet_level;
}

void PlanetEntity::SetPlanetLevel( PlanetLevel *planet_world ){
	this->planet_level = planet_world;
}

bool PlanetEntity::Update( GameEngine *game ){
	bool update_result = this->Entity::Update( game ); // Update Fondamentale

	// il giocatore ha liberato il pianeta, quindi possiamo considerare questo livello come garbage, quindi non sarà più accessibile da questo frame
	if( IsDefined( this->GetPlanetLevel() ) && this->GetPlanetLevel()->IsGenerated() && this->GetPlanetLevel()->IsFree() ){
		update_result = false;
		this->Delete(); // Il Planetlevel associato e questa entità non saranno più significativi
	}
	else if( update_result ){
		// Mi interessa verificare solo la collisione con l'entità giocatore per verificare se vuole entrare nel pianeta
		Player *player = this->GetWorld()->GetPlayer();
		if( this->IsColliding( player ) ){
			this->Callback_OnCollide( game, player, player->GetOrigin() );
			update_result = false;
		}
	}

	return update_result;
}

void PlanetEntity::Draw( ViewPort *view ){
	if( IsDefined( this ) )
		DrawCircle( view, this->world, this->origin, this->radius, COLOR_WHITE );
}

bool PlanetEntity::IsColliding( Entity *entity ){
	if( IsDefined(this) && IsDefined(entity) && this->GetOrigin().DistanceSquared( entity->GetOrigin() ) <= ( this->radius * this->radius ) ){
		return true;
	}
	return false;
}

void PlanetEntity::Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin ){
	if( IsDefined( this ) && IsDefined( collide_ent ) ){
		if( !strcmp( collide_ent->GetClassname(), "Player" ) ){
			Player *player = (Player*)collide_ent;

			// il punto di fuga è vicino al punto di collisione ma distaccato dal punto di -2(direction) unità,
			// così che nel frame successivo alla fuga dal pianeta non sarà ancora eventualemente considerato come in collisione con esso ( anche se non può accadere )
			this->escape_point = hitOrigin;
			Vector direction = player->GetLastMove();
			direction.Scale( -2.0 ); // inverto la direzione con la quale si è diretto verso il pianeta
			this->escape_point.Add( direction );
			this->escape_point = this->GetWorld()->GetNormalizedPoint( this->escape_point );

			// Il giocatore entra nel Livello
			if( IsDefined( this->GetPlanetLevel() ) ){
				this->GetPlanetLevel()->AddEntity( player );
				// Creo il punto di atterraggio nel pianeta
				// GetMaxHeight() è il valore dell'altezza secondo cui si è considerati fuori dal pianeta,
				// quindi dovrà partire dal un'unità più in basso
				Point2D spawn_point = Point2D( 0, player->GetWorld()->GetMaxHeight() - 1 );
				player->SetOrigin( spawn_point );
				game->SetCurrentLevel( this->GetPlanetLevel() );
			}
		}
	}
}
