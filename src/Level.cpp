#include "Level.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
using namespace std;

Level::Level( unsigned int MaxWidth, unsigned int MaxHeight, const char _className[] ) : Entity( NULL, Point2D(0,0), NULL, _className ){
	this->width = MaxWidth;
	if( this->width <= 0 ){
		this->width = 1;
	}

	this->height = MaxHeight;
	if( this->height <= 0 ){
		this->height = 1;
	}

	this->player = NULL;
}

Level::~Level(){
	this->Delete();
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

		list<Entity*>::iterator entity_it; // iteratore che tiene traccia dell'entità corrente
		entity_it = this->entities.begin();

		// NOTA: Soluzione temporanea ma non 100% affidabile;
		// Se il valore puntato da entity_it_next è elimnato da (*entity_it)->Update, nel ciclo successivo entity_it potrebbe accedere ad un area di memoria che potrebbe essere stata eliminata
		while( !this->entities.empty() && entity_it != this->entities.end() ){
			if( IsDefined( *entity_it ) ){
				update_result = (*entity_it)->Update( game ); // EntityUpdateSelector(game, *entity_it );
			}
			
			// Nota: Questo deve essere l'unico punto in cui rimuovo l'entità dalla lista altrimenti l'iteratore attuale
			// potrebbe essere collegato ad un nodo della lista che non mi aspetto se la sua entità associata è rimossa durante l' entity->Update(...)
			// es prima di update *entity_it = entità A
			// dopo update: *entity_it = entità B oppure entity_it = nodo che è stato rimosso dalla lista
			if( !IsDefined( *entity_it ) ){
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
	std::list<Point2D>::iterator surface_it, surface_next_it;
	surface_it = this->surface.begin();
	Color surface = COLOR_GREEN;
	Point2D start, end;
	// TODO: ricontrollare
	while( surface_it != this->surface.end() ){
		start = *surface_it;
		surface_it++;
		end = *surface_it;
		DrawLine( view, this, start, end, surface );
#ifdef DEBUG
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
	}

	for (std::list<Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); it++) {
		if( IsDefined( *it ) ){
			(*it)->Draw( view ); // EntityDrawSelector( view, *it );
		}
	}
	
	if( IsDefined( this->player ) ){
		this->player->Draw( view );
	}
}

void Level::Generate( GameEngine *game ){
	// La classe base Level non fornisce alcuna generazione del terreno, dovranno essere le classe derivate a implementare questo metodo
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

void Level::Delete(){
	this->Entity::Delete();
	
	this->GetOutPlayer();

	// pulisce i dati riigardanti la superficie
	this->surface.clear();

	// pulisco i dati riguardanti le entità in questo livello, e le elimina
	list<Entity*>::iterator entity_iterator = this->entities.begin();
	while( !this->entities.empty() && entity_iterator != this->entities.end() ){
		if( *entity_iterator != NULL ){
			(*entity_iterator)->Delete();
			entity_iterator = this->entities.erase( entity_iterator );
		}
		else{
			entity_iterator++;
		}
	}	
}

list<Entity*> Level::GetEntities( const char *className, bool b_exclude, bool b_search_className_as_subString){
	list<Entity*> ents;
	string *s_ent_classname = NULL;
	bool isClassNameMatching = false;
	for (list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); it++ ) {
		s_ent_classname = new string( (*it)->GetClassname() );
		
		if( className != NULL ){
			if( !b_search_className_as_subString ){
				isClassNameMatching = !s_ent_classname->compare( className ); // !strcmp( (*it)->GetClassname(), className );
			}
			else{
				isClassNameMatching = s_ent_classname->rfind( className ) != s_ent_classname->npos;
			}
		}

		if( className == NULL || (isClassNameMatching && !b_exclude) || (!isClassNameMatching && b_exclude) ){
			ents.push_front( *it );
		}
		
		s_ent_classname->clear();
		delete s_ent_classname;
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
	return !this->surface.empty();
}