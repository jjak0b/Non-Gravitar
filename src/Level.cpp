#include "Entity.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"
#include "Projectile.hpp"
#include "Fuel.hpp"

#include <iostream>
#include <list>
#include <iterator>
using namespace std;

Level::Level(unsigned int MaxWidth, unsigned int MaxHeight, Player *_player) : Entity( NULL, Point2D(0,0), NULL, "Level" ){
	this->width = MaxWidth;
    this->height = MaxHeight;

    if( _player != NULL ){
        this->player = player;
    }
    else{
        this->player = new Player( this, Point2D(  30, 30 ), 150 );
    }

	// TODO: Generazione terreno
	// TODO: Generazione Bunker
	// TODO: Generazione Fuel
};

void Level::SetOrigin(){} // La ridefinizione serve per non renderla visibile esternamente

Point2D Level::GetNormalizedPoint( Point2D _origin ){
	if( _origin.GetX() < 0 ){
		_origin.SetX( this->GetMaxWidth() + _origin.GetX() );
	}
	else{
		_origin.SetX( _origin.GetX() % this->GetMaxWidth() );
	}

	if( _origin.GetY() < 0 ){
		_origin.SetY( 0 );
	}
	else if( _origin.GetY() > this->GetMaxHeight() ){ // non >= perchè se y = this->GetMaxHeight() lo consideriamo come fuori dal livello
		_origin.SetY( this->GetMaxHeight() );
	}

	return _origin;
}

void Level::Update( GameEngine *game ){
	bool shouldUpdateNextFrame = true;
    shouldUpdateNextFrame = this->player->Update( game );
	for (list<Projectile*>::iterator entity_it = this->entities.begin(); entity_it != this->entities.end(); entity_it.operator++ ) {
		if( (*entity_it)->IsDefined() ){
			shouldUpdateNextFrame = (*entity_it)->Update( game );
		}
		else{
			(*it)->Delete();
			// TODO: aggiungere *it ad uno stack di entità da deallocare, tipo un garbage collector
			// TEMP finchè  il TODO precente non è stato effettuato
			delete *it;
			this->entities.erase( it );
		}
	}
}

void Level::Draw( ViewPort *view ){

	if( this->player != NULL ){
		this->player->Draw( view );
	}

	/*for (std::list<Fuel*>::iterator it=this->fuel.begin(); it != this->fuel.end(); ++it) {
		(*it)->Draw( view );
	}*/
	for (std::list<Projectile*>::iterator it=this->projectiles.begin(); it != this->projectiles.end(); ++it) {
		(*it)->Draw( view );
	}
	
}

unsigned int Level::GetMaxHeight(){
    return this->height;
}

unsigned int Level::GetMaxWidth(){
    return this->width;
}

Player *Level::GetPlayer(){
    return this->player;
}

void Level::AddEntity( Entity* entity ){
	// upcasting forzato ma tengo traccia della classe originaria, quindi l'upcasting non avrà conseguenze indesiderate
	if( !strcmp( entity->GetClassname(), "Projectile" ) ){
		Projectile *ent = (Projectile*)entity;
		this->projectiles.push_front( ent );
	}
	else if( !strcmp( entity->GetClassname(), "Bunker" ) ){
		// TODO
	}
}

bool Level::IsColliding( Entity *entity, Point2D *collisionOrigin ){
	if( entity->GetOrigin().GetY() <= 0
	 || entity->GetOrigin().GetY() >= this->GetMaxHeight() ){
		 if( collisionOrigin != NULL ){
			 *collisionOrigin = entity->GetOrigin();
		 }
		 return true;
	}
	else{
		 // TODO: Controllo il segmento/i di terrreno più vicini all'entità
	}
	return false;
}

void Level::Delete( bool b_delete_player ){
	if( b_delete_player && this->player != NULL ){
		this->player->Delete();
		delete this->player;
		this->player = NULL;
	}

	for (list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); it.operator++ ) {
		if( *it != NULL ){
			(*it)->Delete();
			delete *it;
		}
	}
	this->entities.clear();
}

 list<Entity*> Level::GetEntities( const char *className, bool b_exclude ){
	list<Entity*> ents;
	bool isClassNameMatching = false;
	for (list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); it.operator++ ) {
		if( className != NULL ){
			isClassNameMatching = !strcmp( (*it)->GetClassname(), className );
		}
		if( className == NULL || (isClassNameMatching && !b_exclude) || (!isClassNameMatching && b_exclude) ){
			ents.push_front( *it );
		}
	}
	return ents;
 }