#include "Player.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"
#include "GameConfig.h"
#include "Projectile.hpp"
#include "Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

Player::Player( Level *world, Point2D origin, double health ) : DamageableEntity( world, origin, NULL, "Player", health ){
	this->texture = new ColoredBitmap( 3, 5, 0 );
	const BITMAP_DATA_TYPE raw_texturer0[] = " /^\\ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = "|___|";
	const BITMAP_DATA_TYPE raw_texturer2[] = "/   \\";
	/*for( unsigned int j = 0; j < 5; j++ ){
		this->texture->SetValue( raw_texturer0[j], 0, j );
		this->texture->SetValue( raw_texturer1[j], 1, j );
		this->texture->SetValue( raw_texturer2[j], 2, j );
		this->texture->SetValue( raw_texturer3[j], 3, j );
		this->texture->SetValue( raw_texturer4[j], 4, j );
	}*/
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, 3, 5 );
	this->moveOverride = NULL;
}

Player::~Player(){
	this->Delete();
}

void Player::Delete(){
	this->SetMoveOverride( NULL );
	DamageableEntity::Delete();
}

bool Player::Update( GameEngine *game ){
	bool update_result = this->Entity::Update( game );

	if( update_result ){
		INPUT_TYPE input = game->GetkeyPressed();
		Point2D current_origin = this->GetOrigin();	
		Vector direction;

		if( this->moveOverride != NULL ){
			direction = *this->moveOverride;
		}
		else{
			// eventualmente qui ci potrebbe stare uno Vector.Scale( accel )
			// ed impostare la posizione come spostamento r(t) in base al moto uniformemente accelerato
			direction = GetDirectionFromInput( input );
		}
		current_origin.Add( direction ); // la nuova posizione è uguale alla posizione precedente + il vettore spostamento

		if( !direction.IsNull() ){ // aggiorno la posizione solo il vettore spostamento non è nullo
			this->SetOrigin( current_origin );
			this->lastMove = direction;
		}

		if( this->ShouldFire( input ) ){
			this->Fire( this->lastMove );
		}
		else if( this->ShouldBeam( input ) ){
			// TODO: logica del raggio traente
		}

		std::list<Entity*> ents = this->world->GetEntities( "Player", true, false );
		for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
			Point2D *collisionOrigin = NULL;
			if( this->IsColliding( *it, collisionOrigin ) ){
				this->Callback_OnCollide( *it, *collisionOrigin );
				update_result = this->GetHealth() > 0;
			}
		}
		ents.clear();

		this->lastInput = input;
	}
	return update_result;
}

void Player::Draw( ViewPort *view ){
/*#ifdef DEBUG
	if( this->GetWorld() != NULL ){
		Point2D start = this->GetOrigin();
		Vector _direction = GetDirectionFromInput( INPUT_MOVE_RIGHT );

		start.Add( _direction );
		Point2D end = start;

		_direction.Scale( 5.0 );
		end.Add( _direction );
		// DrawLine( view, this->GetWorld(), start, end );
	}
#endif*/
	Entity::Draw( view );
}

Projectile *Player::Fire( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction ); // non lo genero nelle stesse coordinate del giocatore
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 150 );
	return p;
}

bool Player::ShouldFire( INPUT_TYPE input ) {
	return input == INPUT_USE_FIRE;
}

bool Player::ShouldBeam( INPUT_TYPE input) {
	return input == INPUT_USE_BEAM;
}

Vector Player::GetDirectionFromInput( char input ){
	Vector direction = Vector( this->origin.GetSize() );
	switch (input)
	{
		case INPUT_MOVE_UP:
			direction.Set( 1, 1 );
			break;
		case INPUT_MOVE_DOWN:
			direction.Set( 1, -1 );
			break;
		case INPUT_MOVE_LEFT:
			direction.Set( 0, -1 );
			break;
		case INPUT_MOVE_RIGHT:
			direction.Set( 0, 1 );
			break;
		default: // Nessun movimento
			break;
	}

	return direction;
}

char Player::GetLastInput(){
	return this->lastInput;
}
Vector Player::GetLastMove(){
	return this->lastMove;
}

void Player::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage(), hitOrigin, proj );
			proj->Callback_OnCollide( collide_ent, hitOrigin );
		}
		else{ // la collisione contro qualsiasi altra entità, danneggia totalmente il giocatore
			this->DoDamage( this->GetHealth(), hitOrigin, collide_ent );
		}
	}
}

void Player::SetWorld( Level *_world){
	this->Entity::SetWorld( world );
}

void Player::SetMoveOverride( Vector *direction ){
		if( this->moveOverride != NULL ){
			delete this->moveOverride;
		}
		this->moveOverride = direction;
}