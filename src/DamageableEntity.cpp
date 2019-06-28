#include "DamageableEntity.hpp"
#include "Entity.hpp"
#include <cstring>
#include "Projectile.hpp"

DamageableEntity::DamageableEntity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[], double healthmax) : Entity( world, origin, texture, classname ){
	this->SetMaxHealth( healthmax );
	this->SetHealth( healthmax );
	
}

double DamageableEntity::SetMaxHealth( double amount ){
	if (amount < this->health) {
		this->health = amount;
	}

	this->MaxHealth = amount;
	return this->MaxHealth;
}

double DamageableEntity::SetHealth( double amount ){
	this->health = amount;
	return this->health;
}

double DamageableEntity::GetHealth() {
	return this->health;
}

double DamageableEntity::GetMaxHealth() {
	return this->MaxHealth;
}


void DamageableEntity::DoDamage( double amount ) {
	this->health -= amount;
	if (this->health <= 0) {
		this->Delete();
	}
	// if (this-> health -= amount < 0) ???
	//this->Callback_OnHit(damageOrigin, attacker, amount);
}

	/**
	 * @brief recupera una quantità di vita a questa entità
	 * 
	 * @param amount 
	 * @return double 
	 */
double DamageableEntity::DoHeal( double amount ) {
	if (this->health += amount > this->MaxHealth) {
		this->health = this->MaxHealth;
	}
	else
	{
		this->health += amount;
	}
	return health;
	
}

//void Callback_OnHit( Point2D hitOrigin, Entity *attacker, double damage );


 

