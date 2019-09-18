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

    
BunkerC::BunkerC( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerC"){

    this->texture = new Bitmap( 2, 6, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "  _\xDC_ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = " /\xDF\xDF\xDF\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 6 );

	this->GetShape()->addOffset(Point2D( -2, -1 ));
	this->GetShape()->addOffset(Point2D( +2, -1 ));
	this->GetShape()->addOffset(Point2D( -2, +2 ));
	this->GetShape()->addOffset(Point2D( +2, +2 ));
}


bool BunkerC::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );

   if (update_result) {

		if ((game->GetTime() - this->timer) >= 1.5) {

			Vector *direction = new Vector();
			
			direction->Set(0,0);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +2 );
			Shoot(projectile_origin, (*direction));
			
			delete direction;

			if ((game->GetTime() - this->timer) >= 1.6) this->timer = game->GetTime();;
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


void BunkerC::Draw( ViewPort *view ){
	Bunker::Draw( view );
	// DEBUG
// 	list<Point2D> points = this->shape->getPoints();
// 	for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
// 		Point2D point= (*it);
// 	view->Draw(NULL, this->world, point );
// 	}
}
