#include "Bunker.hpp"
#include "BunkerB.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

#include "BunkerBShape.hpp"

    
BunkerB::BunkerB( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerB"){

   this->texture = new Bitmap( 3, 8, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xDC  \xDC  \xDC";
	const BITMAP_DATA_TYPE raw_texturer1[] = "  \\_|_/ ";
	const BITMAP_DATA_TYPE raw_texturer2[] = "  /\xDB\xDB\xDB\\ ";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, NULL, 3, 8 );
}


bool BunkerB::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
    if (update_result) {

		if (this->counter >= 60) {

			Vector *direction = new Vector();
			direction->Set(0,-1);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX() -3, this->origin.GetY() +3 );
			Shoot( projectile_origin, (*direction));
			
			direction->Set(0,0);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +3 );
			Shoot(projectile_origin, (*direction));
			
			direction->Set(0,1);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +3, this->origin.GetY() +3 );
			Shoot(projectile_origin, (*direction));
			
			delete direction;

			counter = 0;
		}

		BunkerBShape bunker_shape = BunkerBShape(this->GetOrigin());
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

void BunkerB::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage());
			proj->Callback_OnCollide();
		}
		else{ 
			this->DoDamage( this->GetHealth());
		}
	}
}

////////////////////////////////////////////////////////////////////
// DEBUG //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void BunkerB::Draw( ViewPort *view ){
	Entity::Draw( view );

	// BunkerBShape test  = BunkerBShape(this->GetOrigin());
	// list<Point2D> points = test.getShapePoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
}

