#include "Bunker.hpp"
#include "BunkerB.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
    
BunkerB::BunkerB( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerB"){

   this->texture = new Bitmap( 3, 8, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xDC  \xDC  \xDC";
	const BITMAP_DATA_TYPE raw_texturer1[] = "  \\_|_/ ";
	const BITMAP_DATA_TYPE raw_texturer2[] = "  /\xDB\xDB\xDB\\ ";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, NULL, 3, 8 );

	this->GetShape()->addOffset(Point2D( -2, 0 ));
	this->GetShape()->addOffset(Point2D( +2, 0 ));
	this->GetShape()->addOffset(Point2D( -3, +5 ));
	this->GetShape()->addOffset(Point2D( +3, +5 ));
}


bool BunkerB::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
	
    if (update_result) {

		if ((game->GetTime() - this->timer) >= 3) {

			Vector *direction = new Vector();
			direction->Set(0,-1);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX() -3, this->origin.GetY() +5 );
			Shoot( projectile_origin, (*direction));
			
			direction->Set(0,0);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +5 );
			Shoot(projectile_origin, (*direction));
			
			direction->Set(0,1);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +3, this->origin.GetY() +5 );
			Shoot(projectile_origin, (*direction));
			
			delete direction;

			this->timer = game->GetTime();
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

void BunkerB::Draw( ViewPort *view ){
	Bunker::Draw( view );
	// DEBUG
	// list<Point2D> points = this->shape->getPoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
}



