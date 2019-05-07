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
	if( this->width <= 0 ){
		this->width = 1;
	}

    this->height = MaxHeight;
	if( this->height <= 0 ){
		this->height = 1;
	}

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
	bool shouldUpdateNextFrame = false;
	if( IsDefined( this->player ) ){
		shouldUpdateNextFrame = this->player->Update( game );
	}
	else{
		this->player->Delete();
		delete this->player;
		this->player = NULL;
	}

	if( shouldUpdateNextFrame ){
		bool update_result = false;
		for (list<Entity*>::iterator entity_it = this->entities.begin(); entity_it != this->entities.end(); entity_it++ ) {
			if( IsDefined( *entity_it ) ){
				update_result = EntityUpdateSelector(game, *entity_it );
			}
			else{
				(*entity_it)->Delete();
				// TODO: aggiungere *it ad uno stack di entità da deallocare, tipo un garbage collector
				// TEMP finchè  il TODO precedente non è stato effettuato
				delete *entity_it;
				this->entities.erase( entity_it );
			}
		}
	}
	return shouldUpdateNextFrame;
}

bool EntityUpdateSelector( GameEngine *game, Entity *entity ){
	bool update_result = false;
	if( IsDefined( entity ) ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			Player *ent = (Player*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "Level" ) ){
			Level *ent = (Level*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "Planet" ) ){
			Planet *ent = (Planet*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "SolarSystem" ) ){
			SolarSystem *ent = (SolarSystem*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "Projectile" ) ){
			Projectile *ent = (Projectile*)entity;
			update_result = ent->Update( game );
		}
		// TODO: aggiungere altri tipi di Update
		else{
			update_result = entity->Update( game );
		}
	}
	
	return update_result;
}

void EntityDrawSelector( ViewPort *view, Entity *entity ){
	if( IsDefined( entity ) ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			Player *ent = (Player*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "Level" ) ){
			Level *ent = (Level*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "Planet" ) ){
			Planet *ent = (Planet*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "SolarSystem" ) ){
			SolarSystem *ent = (SolarSystem*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "Projectile" ) ){
			Projectile *ent = (Projectile*)entity;
			ent->Draw( view );
		}
		// TODO: aggiungere altri tipi di Draw
		else{
			entity->Draw( view );
		}
	}
}

void Level::Draw( ViewPort *view ){
	for (std::list<Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); it++) {
		EntityDrawSelector( view, *it );
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
		entity->SetWorld( this );
	}
}

void Level::RemoveEntity( Entity *entity ){
	if( entity != NULL ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			this->GetOutPlayer();
		}
		else{
			this->entities.remove( entity );
		}
		entity->SetWorld( NULL );
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

	for (list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); it++ ) {
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
	for (list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); it++ ) {
		if( className != NULL ){
			isClassNameMatching = !strcmp( (*it)->GetClassname(), className );
		}
		if( className == NULL || (isClassNameMatching && !b_exclude) || (!isClassNameMatching && b_exclude) ){
			ents.push_front( *it );
		}
	}
	return ents;
}

Player *Level::GetOutPlayer(){
	Player *_player = this->GetPlayer();
	this->player = NULL;
	_player->SetWorld( NULL );
	return _player;
}
