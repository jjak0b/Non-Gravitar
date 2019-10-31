#include "Level.hpp"
#include "Player.hpp"
#include "engine/GameEngine.hpp"
#include "shared/Utility.h"
#include <cstring>

using namespace std;

Level::Level( Vector _bounds, const char _className[] ) : Entity( NULL, Point2D(0,0), NULL, _className ){
	VECTOR_VALUE_TYPE bound_value = 1;
	for( int i = 0; i < _bounds.GetSize(); i++ ){
		if( _bounds.Get( i, &bound_value ) ){
			if( bound_value <= 0 ){
				_bounds.Set( i, 1.0 );
			}
		}
	}
	this->bounds = _bounds;
	this->player = NULL;
	this->SetWorld( this );
	this->isGenerated = false;
}

Level::~Level(){
    this->entities.clear();
}

void Level::SetOrigin(){} // La ridefinizione serve per non renderla visibile esternamente

Point2D Level::GetNormalizedPoint( Point2D _origin ){
	if( _origin.GetX() < 0 ){
		_origin.SetX( this->GetMaxWidth() + _origin.GetX() );
	}
	else{
				int point_int_value = _origin.GetX();
		_origin.SetX( point_int_value % this->GetMaxWidth() + ( _origin.GetX() - point_int_value ) );
	}

	if( _origin.GetY() < 0 ){
		_origin.SetY( 0 );
	}
	else if( _origin.GetY() > this->GetMaxHeight() ){ // non >= perchè se y = this->GetMaxHeight() lo consideriamo come fuori dal livello
		_origin.SetY( this->GetMaxHeight() );
	}

	return _origin;
}

Vector Level::GetBounds(){
	return this->bounds;
}

bool Level::Update( GameEngine *game ){
	if( !this->Entity::Update( game ) ){
		return false;
	}
	else if( !this->IsGenerated() ){
		this->Generate( game );
	}

	bool shouldUpdateNextFrame = false;
	if( IsDefined( this->GetPlayer() ) ){
		shouldUpdateNextFrame = this->GetPlayer()->Update( game );
	}

	if( shouldUpdateNextFrame ){
		bool update_result = false;

		std::list<Entity*>::iterator entity_it, entity_it_2; 
		list<Entity*> ents = GetEntities(NULL, false, false);
		entity_it = ents.begin();
		Entity *entity = NULL;
#ifdef ENABLE_COLLISION_LEVEL
		while( IsDefined(this) && !ents.empty() && entity_it != ents.end() ) {
			entity = *entity_it;
			if ( IsDefined( entity ) ) {
				if ( this->IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
						game,
#endif
						entity ) ) {
					entity->Callback_OnCollide(game, this);
				}
			}
			entity_it++;
#ifdef DEBUG_COLLISION_DRAWING
			if( this->GetShape() != NULL )
				this->GetShape()->UpdateAbsolutes( origin );
#endif
		}
#endif
		entity_it = ents.begin();
#ifdef ENABLE_COLLISION_ENTITIES
		Entity *entity2 = NULL;
		while( !ents.empty() && entity_it != ents.end() ) {
			entity = *entity_it;
			entity_it_2 = ents.begin();
			while( IsDefined( entity ) && !ents.empty() && entity_it_2 != ents.end() ) {
				entity2 = *entity_it_2;
				if ( entity != entity2 && IsDefined( entity2 ) && entity->IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
						game,
#endif
						entity2 ) ) {
					entity2->Callback_OnCollide(game, entity );

				}
#ifdef DEBUG_COLLISION_DRAWING
				if( entity->GetShape() != NULL ){
					entity->GetShape()->UpdateAbsolutes( entity->GetOrigin() );
				}
				if( entity2->GetShape() != NULL ){
					entity2->GetShape()->UpdateAbsolutes( entity2->GetOrigin() );
				}
#endif
				entity_it_2++;
			}
			entity_it++;
		}
#endif
		// NOTA: Soluzione temporanea ma non 100% affidabile;
		// Se il valore puntato da entity_it_next è elimnato da (*entity_it)->Update, nel ciclo successivo entity_it potrebbe accedere ad un area di memoria che potrebbe essere stata eliminata
		entity_it = this->entities.begin();
		while( !this->entities.empty() && entity_it != this->entities.end() ){
			entity = *entity_it;
			if( IsDefined( entity ) ){
				update_result = entity->Update( game ); // EntityUpdateSelector(game, *entity_it );
			}
			
			// Nota: Questo deve essere l'unico punto in cui rimuovo l'entità dalla lista altrimenti l'iteratore attuale
			// potrebbe essere collegato ad un nodo della lista che non mi aspetto se la sua entità associata è rimossa durante l' entity->Update(...)
			// es prima di update *entity_it = entità A
			// dopo update: *entity_it = entità B oppure entity_it = nodo che è stato rimosso dalla lista
			if( !IsDefined( entity ) ){
				entity_it = this->entities.erase( entity_it );
			}
			else{
				entity_it++;
			}
		}
	}

	return shouldUpdateNextFrame;
}

void Level::Draw( ViewPort *view ){

#ifndef DEBUG_COLLISION_DRAWING
	if (this->shape != NULL) {
		list<Point2D> surface_points = this->shape->getOffsetPoints();
		std::list<Point2D>::iterator surface_it, surface_next_it;
		surface_it = surface_points.begin();
		Color surface = COLOR_GREEN;
		Point2D
			start =  surface_points.back(),
			end;

		while( surface_it != surface_points.end() ){
			end = *surface_it;
			start = this->GetNormalizedPoint( start );
			end = this->GetNormalizedPoint( end );

			DrawLine( view, this, start, end, surface );
	#ifdef DEBUG_SURFACE_TERRAIN
			const int size_str_buffer = 30;
			char str_print_buffer[size_str_buffer] = "";
			Point2D temp;

			snprintf( str_print_buffer, size_str_buffer, "(%.2f,\n%.2f)", start.GetX(), start.GetY() );
			temp = start;
			temp.SetY( temp.GetY() + 3 );
			view->Print( str_print_buffer, view->WorldPointToViewPoint( this, temp ), COLOR_WHITE );

			snprintf( str_print_buffer, size_str_buffer, "(%.2f,\n%.2f)", end.GetX(), end.GetY() );
			temp = end;
			temp.SetY( temp.GetY() + 3 );
			view->Print( str_print_buffer, view->WorldPointToViewPoint( this, temp ), COLOR_WHITE );
	#endif
			start = end;
			surface_it++;
		}
	}

	for (std::list<Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); it++) {
		if( IsDefined( *it ) ){
			(*it)->Draw( view ); // EntityDrawSelector( view, *it );
		}
	}
	
	if( IsDefined( this->player ) ){
		this->player->Draw( view );
	}
#else
	Color c = Color( 255, 255, 0 );
	std::list<Entity*> ents;
#ifdef DEBUG_COLLISION_ENTITIES
	ents = GetEntities( NULL, false, false );
#endif
#ifdef DEBUG_COLLISION_SURFACE_TERRAIN
#ifndef DEBUG_COLLISION_ENTITIES
	ents.push_front( this->player );
#endif
	ents.push_front( this );
#endif
	for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
		Entity* ent = *it;
		if( IsDefined( ent  ) ){
			if( ent->GetShape() != NULL ) {
				std::list<Point2D> points = ent->GetShape()->getAbsolutes();
				Point2D
					start = points.back(),
					end;
				std::list<Point2D>::iterator it_p = points.begin();
				while ( !points.empty() && it_p != points.end()) {
					end = *it_p;
					view->Draw( NULL, this, start );
					view->Draw( NULL, this, end );
					DrawLine(view, this, start, end, c );
					start = end;
					it_p++;
				}
			}
		}
	}
#endif
}

int Level::ShouldGenerate(ViewPort *view){
    return false;
}

void Level::Generate( GameEngine *game ){
	// La classe base Level non fornisce alcuna generazione del terreno, dovranno essere le classe derivate a implementare questo metodo
}

unsigned int Level::GetMaxHeight(){
	VECTOR_VALUE_TYPE value = 1;
	this->bounds.Get( BOUND_INDEX_HEIGHT, &value );
	return (unsigned int)value;
}

unsigned int Level::GetMaxWidth(){
	VECTOR_VALUE_TYPE value = 1;
	this->bounds.Get( BOUND_INDEX_WIDTH, &value );
	return (unsigned int)value;
}

Player *Level::GetPlayer(){
	return this->player;
}

void Level::AddEntity( Entity *entity ){
	if( IsDefined( entity ) ){
		Level *world_entity = entity->GetWorld();
		if( world_entity != this ){
			if( !strcmp( entity->GetClassname(), "Player" ) ){
				if( IsDefined( world_entity ) ){
					world_entity->GetOutPlayer();
				}
				this->player = (Player*)entity;
			}
			else{
				if( IsDefined( world_entity ) && !world_entity->entities.empty() ){
					world_entity->entities.remove( entity );
				}
				this->entities.push_back( entity );			
			}
			entity->SetWorld( this );
		}
	}
}

// bool Level::IsColliding( Entity *entity, Point2D *collisionOrigin ){
// 	if( entity->GetOrigin().GetY() <= 0
// 	 || entity->GetOrigin().GetY() >= this->GetMaxHeight() ){
// 		 if( collisionOrigin != NULL ){
// 			 *collisionOrigin = entity->GetOrigin();
// 		 }
// 		 return true;
// 	}
// 	else{
// 		 // TODO: Controllo il segmento/i di terrreno più vicini all'entità
// 	}
// 	return false;
// }

void Level::Delete( GameEngine* game ){
	this->GetOutPlayer();

	// pulisce i dati riigardanti la superficie
	this->shape->deleteAbsolutes();

	// pulisco i dati riguardanti le entità in questo livello, e le elimina
	list<Entity*>::iterator entity_iterator = this->entities.begin();
	while( !this->entities.empty() && entity_iterator != this->entities.end() ){
		if( *entity_iterator != NULL ){
			(*entity_iterator)->Delete( game );
			entity_iterator = this->entities.erase( entity_iterator );
		}
		else{
			entity_iterator++;
		}
	}
	Entity::Delete( game );
}

list<Entity*> Level::GetEntities( const char *className, bool b_exclude, bool b_search_className_as_subString){
	list<Entity*> ents;

	if( className != NULL ){
		ents = list<Entity*>();
		bool isClassNameMatching;
		list<Entity*>::iterator it = this->entities.begin();
		bool keep_checking = !this->entities.empty();
		Entity* ent = NULL;
		while( keep_checking ) {
			keep_checking  = it != this->entities.end();
			if( keep_checking ){
				ent = *it;
				it++; // l'iteratore punta all'entità successiva  per il ciclo successivo
			}
			else{	
				ent = this->player;
			}

			if ( ent != NULL) {

				isClassNameMatching = Utility::CheckEqualsOrSubstring( ent->GetClassname(), className, b_search_className_as_subString );

				if ( ( isClassNameMatching && !b_exclude ) || ( !isClassNameMatching && b_exclude ) ) {
					ents.push_front(ent);
				}
			}
		}
	}
	else{
		ents = this->entities;// stdlist implementa l'operatore '=' com metodo per copiare completamente una lista con i suoi elementi.
		if( this->player != NULL )
			ents.push_front( this->player );
	}
	return ents;
}

Player *Level::GetOutPlayer(){
	Player *_player = this->player;
	if( this->player != NULL ){
		this->player->SetWorld( NULL );
		this->player = NULL;
	}
	return _player;
}

bool Level::IsGenerated(){
	return isGenerated;
}


