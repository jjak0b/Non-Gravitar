#include "BunkerA.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <ctime>
#include <cstring>

BunkerA::BunkerA( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerA"){

    this->texture = new Bitmap( 2, 3, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "q_p";
	const BITMAP_DATA_TYPE raw_texturer1[] = "/\xDB\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 3);

}


bool BunkerA::Update(GameEngine* game) {
    bool update_result = Bunker::Update( game );

	if (update_result) {
		if (this->counter >= 40) {

			int r1 = random(4);
			int r2 = random (4);
			while (r1 == r2) r2 = random(4);

			Vector *direction = new Vector();
			direction->Set(0,r1);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX() -1, this->origin.GetY() +1 );
			Shoot( projectile_origin, (*direction));

			direction->Set(0,r2);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +1, this->origin.GetY() +1 );
			Shoot( projectile_origin, (*direction));

			delete direction;

			counter = 0;
    	}

		// BunkerAShape bunker_shape = BunkerAShape(this->GetOrigin());
		// std::list<Entity*> ents = this->world->GetEntities( "Projectile", false, true );
		// for (std::list<Entity*>::iterator it = ents.begin(); update_result && it != ents.end(); it++) {
		// 	if( bunker_shape.PointCollision((*it)->GetOrigin()) ){
		// 		Projectile *proj = (Projectile*)(*it);
		// 		proj->Callback_OnCollide( this );
		// 		update_result = this->GetHealth() > 0;
		// 	}
		// }
    }
	return update_result;
	
}


void BunkerA::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			proj->Callback_OnCollide( this );
		}
		else{ 
			this->DoDamage( this->GetHealth());
		}
	}
}


////////////////////////////////////////////////////////////////////
// DEBUG //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void BunkerA::Draw( ViewPort *view ){
	Bunker::Draw( view );

	// BunkerAShape test  = BunkerAShape(this->GetOrigin());
	// list<Point2D> points = test.getShapePoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
}
