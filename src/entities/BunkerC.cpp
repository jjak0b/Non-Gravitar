#include "Bunker.hpp"
#include "BunkerC.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

#include "BunkerCShape.hpp"

    
BunkerC::BunkerC( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerC"){

    this->texture = new Bitmap( 2, 6, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "  _\xDC_ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = " /\xDF\xDF\xDF\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 6 );
}


bool BunkerC::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );

   if (update_result) {

		if (this->counter >= 30) {

			Vector *direction = new Vector();
			
			direction->Set(0,0);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +1 );
			Shoot(projectile_origin, (*direction));
			
			delete direction;

			if (counter >= 31) counter = 0;
		}

		BunkerCShape bunker_shape = BunkerCShape(this->GetOrigin());
		std::list<Entity*> ents = this->world->GetEntities( "Projectile", false, true );
		for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
			if( bunker_shape.PointCollision((*it)->GetOrigin()) ){
				Projectile *proj = (Projectile*)(*it);
				this->DoDamage( proj->GetDamage());
				(*it)->Delete();
				update_result = this->GetHealth() > 0;
			}
		}
    }
    return update_result;

}

void BunkerC::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage());
			proj->Delete();
		}
		else{ 
			this->DoDamage( this->GetHealth());
		}
	}
}

////////////////////////////////////////////////////////////////////
// DEBUG //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void BunkerC::Draw( ViewPort *view ){
	Entity::Draw( view );

	// BunkerCShape test  = BunkerCShape(this->GetOrigin());
	// list<Point2D> points = test.getShapePoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
}
