#include "Planet.hpp"
#include "GameEngine.hpp"
#include "SolarSystem.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Point2D.hpp"
#include <cstring>

Planet::Planet( SolarSystem *_solarSystem, Point2D _origin, unsigned int _radius, unsigned int _max_longitude, unsigned int _max_altitude ) : Entity( _solarSystem, _origin, NULL, "Planet"){
	this->radius = _radius;
	this->max_longitude = _max_longitude;
	this->max_altitude = _max_altitude;
}

bool Planet::Update( GameEngine *game ){
	Player *p = this->world->GetPlayer();
	if( this->IsColliding( p ) ){
		this->Callback_OnCollide( game, p, p->GetOrigin() );
		return false;
	}

	if( this->subWorld != NULL && this->subWorld->IsGarbage() ){
		return false;
	}
	return true;
}

void Planet::Draw( ViewPort *view ){
	DrawCircle( view, this->world, this->origin, this->radius );
}

bool Planet::IsColliding( Entity *entity ){
	if( entity != NULL && this->GetOrigin().Distance( entity->GetOrigin() ) <= this->radius ){
		return true;
	}
	return false;
}

void Planet::Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Player" ) ){
			Player *player = (Player*)collide_ent;
			this->player = player->GetWorld()->GetOutPlayer();

			if( this->subWorld == NULL ){
				this->subWorld = new Level( NULL, this->max_longitude, this->max_altitude, "Level", this->player );
			}
			else{
				this->subWorld->AddEntity( this->player );
			}
			game->SetCurrentLevel( this->subWorld );
		}
	}
}