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

#include "Bunker.hpp"
#include "BunkerA.hpp"
#include "BunkerB.hpp"
#include "Point2D.hpp"

Player::Player( Level *world, Point2D origin, double health) : DamageableEntity( world, origin, NULL, "Player", health ){
	this->texture = new ColoredBitmap( 3, 5, 0 );
	const BITMAP_DATA_TYPE raw_texturer0[] = " /^\\ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = "|___|";
	const BITMAP_DATA_TYPE raw_texturer2[] = "/   \\";
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

			this->RemoveFuel(1);
			this->SetOrigin( current_origin );
			this->lastMove = direction;
		}

		if( this->ShouldFire( input ) ){
			this->Fire( this->lastMove );
		}
		else if( this->ShouldBeam( input ) ){
			this->Beam(this->lastMove);
		}

		std::list<Entity*> ents = this->world->GetEntities( "Player", true, false );
		for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
			if( this->IsColliding( *it, NULL ) ){
				this->Callback_OnCollide( *it, this->GetOrigin() );
				update_result = this->GetHealth() > 0;
			}
		}
		ents.clear();

		this->lastInput = input;
	}
	return update_result;
}

void Player::Draw( ViewPort *view ){
	Entity::Draw( view );

	const int size_str_buffer = 30;
	char str_print_buffer[ size_str_buffer ] = "";

	Point2D point_top_left_hud = Point2D( 0, view->GetHeight() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Score: [value]"); // TODO: aggiungere valore dopo implementazione
	view->Print( str_print_buffer, point_top_left_hud );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "fuel: %.2f / %.2f", this->GetFuel(), this->GetMaxFuel() );
	view->Print( str_print_buffer, point_top_left_hud );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Health: %.2f / %.2f", this->GetHealth(), this->GetMaxHealth() );
	view->Print( str_print_buffer, point_top_left_hud );
}

Projectile *Player::Fire( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction ); // non lo genero nelle stesse coordinate del giocatore
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 10, "Projectile" );
	return p;
}

Projectile *Player::Beam( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction ); 
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 0, "Beam" );
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
			this->DoDamage( proj->GetDamage());
			proj->Callback_OnCollide();
		}
		if( !strcmp( collide_ent->GetClassname(), "Beam" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			proj->Callback_OnCollide();
		}
		if( !strcmp( collide_ent->GetClassname(), "Bunker" ) ){
			this->Delete();
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


void Player::SetMaxFuel( double amount ){
	if (amount < this->fuel) {
		this->fuel = amount;
	}

	this->MaxFuel = amount;
}

void Player::SetFuel( double amount ){
	this->fuel = amount;
}

double Player::GetFuel() {
	return this->fuel;
}

double Player::GetMaxFuel() {
	return this->MaxFuel;
}


void Player::AddFuel( double amount ) {
	if (this->fuel += amount > this->MaxHealth) {
		this->fuel = this->MaxFuel;
	}
	else
	{
		this->fuel += amount;
	}
	
}

void Player::RemoveFuel( double amount ) {
	this->fuel -= amount;
	if (this->fuel <= 0) {
		this->Delete();
	}
}