#include "Entity.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"
#include "Projectile.hpp"
#include "Fuel.hpp"
#include "Planet.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
using namespace std;

Level::Level( Level *parentWorld, unsigned int MaxWidth, unsigned int MaxHeight, const char _className[], Player *_player) : Entity( parentWorld, Point2D(0,0), NULL, _className ){
	this->width = MaxWidth;
    this->height = MaxHeight;

    if( _player != NULL ){
        this->player = player;
    }
    else{
        this->player = new Player( this, Point2D( this->width/2, this->height/2 ), 150 );
    }
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

bool Level::Update( GameEngine *game ){
	bool shouldUpdateNextFrame = true;
	shouldUpdateNextFrame = this->player->Update( game );

	for (list<Entity*>::iterator entity_it = this->entities.begin(); entity_it != this->entities.end(); entity_it.operator++ ) {
		if( IsDefined( *entity_it ) ){
			(*entity_it)->Update( game );
		}
		else{
			(*entity_it)->Delete();
			// TODO: aggiungere *it ad uno stack di entità da deallocare, tipo un garbage collector
			// TEMP finchè  il TODO precedente non è stato effettuato
			delete *entity_it;
			this->entities.erase( entity_it );
		}
	}

	return shouldUpdateNextFrame;
}

void Level::Draw( ViewPort *view ){
	for (std::list<Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); it.operator++) {
		if( !strcmp( (*it)->GetClassname(), "Planet" ) ){
			Planet *ent = (Planet*)(*it);
			ent->Draw( view );
		}
		else if( !strcmp( (*it)->GetClassname(), "Projectile" ) ){
			Projectile *ent = (Projectile*)(*it);
			ent->Draw( view );
		}
		else{
			(*it)->Draw( view );
		}
	}
	
	if( this->player != NULL ){
		this->player->Draw( view );
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
	if( IsDefined( entity ) ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			this->player = (Player*)entity;
		}
		else{
			this->entities.push_front( entity );
		}
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