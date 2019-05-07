#include "Planet.hpp"
#include "GameEngine.hpp"
#include "SolarSystem.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Point2D.hpp"
#include <cstring>
#include <cmath>

Planet::Planet( SolarSystem *_solarSystem, Point2D _origin, unsigned int _circumference ) : Entity( _solarSystem, _origin, NULL, "Planet"){
	this->circumference = _circumference;
	this->player = NULL;
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
	double radius = this->circumference / 2.0;
	DrawCircle( view, this->world, this->origin, radius );
}

bool Planet::IsColliding( Entity *entity ){
	// TODO
	return false;
}

void Planet::Callback_OnCollide( GameEngine *game, Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Player" ) ){
			this->player = this->world->GetOutPlayer();
			if( this->subWorld == NULL ){
				unsigned int width = circumference;
				unsigned int height = circumference / 360;
				this->subWorld = new Level( NULL, width, height, "Level", this->player );
			}
			else{
				this->subWorld->AddEntity( this->player );
			}
			game->SetCurrentLevel( this->subWorld );
		}
	}
}