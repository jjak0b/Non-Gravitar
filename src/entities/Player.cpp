#include "Player.hpp"
#include "Projectile.hpp"
#include "PlayerProjectile.hpp"
#include "PlayerBeam.hpp"
#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "shared/Utility.h"
#include <cstring>

Player::Player( Level *world, Point2D origin, double health = PLAYER_HEALTH ) : DynamicEntity( world, origin, NULL, "Player", PLAYER_MAX_SPEED ), Damageable(health) {

	this->moveOverride = NULL;
	this->MaxFuel = PLAYER_MAX_FUEL;
	this->fuel = this->MaxFuel;
	this->score = 0;
	
	this->texture = new Bitmap( 2, 9, COLOR_RED );
	const BITMAP_DATA_TYPE  raw_texturer0[] = "  /%\xB1\xB1\\  ";
	const BITMAP_DATA_TYPE  raw_texturer1[] = "(%\xDB\xDB\xDB\xDB\xDB\xDB)";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1 };
	
	const Color COLOR_LIGHTBLUE = Color( 135, 206, 250 );
	const Color COLOR_STEELBLUE = Color( 70, 130, 180 );
	
	const Color colors_r0[] = { COLOR_TRANSPARENT, COLOR_TRANSPARENT, COLOR_GREY, COLOR_LIGHTBLUE, COLOR_LIGHTBLUE, COLOR_LIGHTBLUE, COLOR_GREY, COLOR_TRANSPARENT, COLOR_TRANSPARENT };
	const Color colors_r1[] = { COLOR_GREY, COLOR_LIGHTBLUE, COLOR_STEELBLUE, COLOR_STEELBLUE, COLOR_STEELBLUE, COLOR_STEELBLUE, COLOR_STEELBLUE, COLOR_STEELBLUE, COLOR_GREY };
	const Color *colorTable[] = { colors_r0, colors_r1 };
	this->texture->Load( rawtexture, colorTable, 2, 9 );
	
	
	this->shape = new Shape();
	this->shape->addOffset(Point2D( -4, 2 ), origin);
	this->shape->addOffset(Point2D( -4, -1 ), origin);
	this->shape->addOffset(Point2D( +4, -1 ), origin);
	this->shape->addOffset(Point2D( +4, 2 ), origin);
}

Player::~Player(){
	if( moveOverride != NULL ){
	    delete moveOverride;
	}
}

void Player::Delete(GameEngine* game ){;
	this->SetMoveOverride( NULL );
    Entity::Delete( game );
}

bool Player::Update( GameEngine *game ){
	bool update_result = DynamicEntity::Update( game );
	
	if( update_result ){

		if( IsDefined( this ) ){
			if( !update_result || this->GetFuel() <= 0 || this->GetHealth() <= 0 ){
                update_result = false;
			}
		}

		if ( !update_result ){
            this->Delete( game );
		}
		else{
			INPUT_TYPE input = game->GetkeyPressed();
			Vector direction;

			if (this->moveOverride != NULL) {
				direction = *this->moveOverride;
			}
			else{
				direction = GetDirectionFromInput(input);
			}
#ifdef DEBUG
			Point2D current_origin = this->GetOrigin();
			current_origin.Add(direction);

			if (!direction.IsNull()) { // aggiorno la posizione solo il vettore spostamento non è nullo
				// this->RemoveFuel(1);
				this->SetOrigin(current_origin);
				this->lastMove = direction;
			}
#else
			double fuel_used_amount = 0.0;
			Vector _acceleration = direction;
			if ( !direction.IsNull() ) { // aggiorno la posizione solo il vettore spostamento non è nullo
				Vector direction_inverted = direction;
				direction_inverted.Scale( -1.0 );

				VECTOR_VALUE_TYPE speed = this->GetSpeed();
				if( this->lastMove.Equals( direction_inverted ) ){ // Se il giocatore vuole andare nella direzione opposta, allora lo rallento
					_acceleration.Scale( -speed );
				}
				else{ // altrimenti va nella direzione di movimento
					_acceleration.Scale( PLAYER_MAX_SPEED );
				}

				_acceleration = direction;
				_acceleration.Scale( PLAYER_MAX_ACCELERATION );
				this->AddAcceleration( _acceleration );
				this->lastMove = direction;
				fuel_used_amount += PLAYER_MAX_ACCELERATION * (2.0/100.0);
			}
			// ricevo un rallentamento di "attrito" nella direzione opposta a quella di movimento per rallentare il giocatore, migliorando il suo controllo
			_acceleration.Add( GetVelocity().Scale( -PLAYER_FRICTION_COEFFICIENT ) ); // a_f = - v * C

			this->AddAcceleration( _acceleration );

			if( GetSpeed() > 0.1 ){
			#ifndef DEBUG
				this->RemoveFuel( fuel_used_amount );
			#endif
			}
#endif		
			// Generazione proiettile
			if (this->ShouldFire(input) && (game->GetTime() - this->fireTime) >= PLAYER_FIRE_DELAY ) {
				Vector direction = this->GetVelocity();
				if( !direction.IsNull() )
					direction.Normalize();
				
#ifndef DEBUG
				this->Fire( direction );
#else
				this->Fire(lastMove);
#endif		
				this->fireTime = game->GetTime();
			}
			// Generazione raggio traente
			else if (this->ShouldBeam(input) && (game->GetTime() - this->beamTime) >= PLAYER_BEAM_DELAY) {
				this->Fire_Beam();

				this->beamTime = game->GetTime();
			}

			this->lastInput = input;
		}
	}
	return update_result;
}

void Player::Draw( ViewPort *view ){
	Entity::Draw( view );

	const int size_str_buffer = 30;
	char str_print_buffer[ size_str_buffer ] = "";

	// HUD del giocatore che mostra il suo status
	Point2D point_top_left_hud = Point2D( 0, view->GetHeight() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Score: %d", this->GetScore());
	view->Print( str_print_buffer, point_top_left_hud, COLOR_RED );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Fuel: %.2f / %.2f", this->GetFuel(), this->GetMaxFuel() );
	view->Print( str_print_buffer, point_top_left_hud, COLOR_BLUE );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Health: %.2f / %.2f", this->GetHealth(), this->GetMaxHealth() );
	view->Print( str_print_buffer, point_top_left_hud, COLOR_GREEN );
}

Projectile *Player::Fire( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	
	Vector temp = direction;
	projectile_origin.Add( temp ); // non lo genero nelle stesse coordinate del giocatore

	Projectile *p = new PlayerProjectile( this->world, projectile_origin, direction, PLAYER_PROJECTILE_SPEED, PLAYER_FIRE_DAMAGE );
	return p;
}

PlayerBeam *Player::Fire_Beam( ){
	Point2D projectile_origin = this->GetOrigin();
	Vector direction;
	direction.Set(1, -1);
	projectile_origin.Add( direction );
	Vector temp = direction;
	
	temp.Scale(2); // Scalo la direzione per farlo sparare oltre la collision shape
	projectile_origin.Add( temp ); // non lo genero nelle stesse coordinate del giocatore

	PlayerBeam *p = new PlayerBeam( this->world, projectile_origin, direction, PLAYER_BEAM_SPEED );
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

void Player::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( IsDefined( collide_ent ) ){
		if( !strcmp( collide_ent->GetClassname(), "Player_Projectile" ) ){
			return;
		}
#ifdef DEBUG
		cout << " DETECTED COLLISION: " << collide_ent->GetClassname() << endl << "( " << collide_ent->GetOrigin().GetX() << " , " << collide_ent->GetOrigin().GetY() << " ) "<<endl;
		DrawLine(game->GetViewport(), this->world, this->origin, collide_ent->GetOrigin(), COLOR_RED );
#endif
		// Collisione contro il terreno -> infligge danno e riporta il giocatore in una posizione opposta a quella di movimento
		if( Utility::CheckEqualsOrSubstring( collide_ent->GetClassname(), "Level", true ) ){
#ifndef DEBUG
			this->DoDamage( PLAYER_COLLISION_DAMAGE );
#endif
			Point2D safe_origin = this->GetOrigin();
			safe_origin.Add( this->GetVelocity().Scale( -1.0 ) );
			this->SetVelocity( Vector( safe_origin.GetSize() ) );
			this->SetOrigin( safe_origin );
		}
		// Collisione contro un proiettile
		else if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			
#ifdef DEBUG_COLLISION_DRAWING
			DrawLine( game->GetViewport(), this->world, proj->GetOrigin(), collide_ent->GetOrigin(), COLOR_RED );
#else
			this->DoDamage( proj->GetDamage());
#endif
		}
		// Collisione contro un Bunker
		else if( Utility::CheckEqualsOrSubstring( collide_ent->GetClassname(), "Bunker", true ) ){
			this->DoDamage( this->GetHealth() );
		}
		else if( !strcmp( collide_ent->GetClassname(), "PlanetEntity" ) ) {
			PlanetEntity* planet = (PlanetEntity*)collide_ent;
			if( IsDefined( planet->GetPlanetLevel() ) && !planet->GetPlanetLevel()->IsFree() ) {
				// il punto di fuga è vicino al punto di collisione ma distaccato dal punto di -2(direction) unità,
				// così che nel frame successivo alla fuga dal pianeta non sarà ancora eventualemente considerato come in collisione con esso ( anche se non può accadere )

				// inverto la direzione con la quale si è diretto verso il pianeta
				planet->escape_direction = this->GetVelocity();
				planet->escape_direction.Normalize();
				planet->escape_direction.Scale(-1.0);

				planet->escape_point = this->GetOrigin();
				Vector escape_offset = planet->escape_direction;
				escape_offset.Scale(
						2.0); // Aggiungo un offset per esere sicuro di non tornare nuovamente nel raggio di collisioni del pianeta
				planet->escape_point.Add(escape_offset);
				planet->escape_point = planet->GetWorld()->GetNormalizedPoint(planet->escape_point);
				// Il giocatore entra nel Livello

				if (IsDefined(planet->GetPlanetLevel())) {
					planet->GetPlanetLevel()->AddEntity(this);
					// Creo il punto di atterraggio nel pianeta
					// GetMaxHeight() è il valore dell'altezza secondo cui si è considerati fuori dal pianeta,
					// quindi dovrà partire dal un'unità più in basso
					Point2D spawn_point = Point2D(0, this->GetWorld()->GetMaxHeight() - 1);
					this->SetOrigin(spawn_point);

					Vector direction = Vector(spawn_point.GetSize());
					direction.Set(1, -1);
					VECTOR_VALUE_TYPE speed = this->GetSpeed();
					// Azzero la velocità attuale, così la velocità iniziale sarà 0
					// ed entrerà nel pianeta con velocità molto rallentata
					this->SetVelocity(
							Vector(direction.GetSize())); 
					this->SetVelocity(direction.Scale(speed));

					game->SetCurrentLevel(planet->GetPlanetLevel());
				}
			}
		}
	}
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
	this->fuel += amount;
	if (this->fuel > this->MaxFuel) {
		this->fuel = this->MaxFuel;
	}
}

void Player::RemoveFuel( double amount ) {
	this->fuel -= amount;
	if (this->fuel < 0) {
		this->fuel = 0;
	}
}

unsigned int Player::GetScore(){
	return this->score;
}

void Player::AddScore(unsigned int value) {
	this->score += value;
}

