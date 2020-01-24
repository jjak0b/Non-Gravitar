#include "Damageable.hpp"

Damageable::Damageable( double healthmax){
	this->SetMaxHealth( healthmax );
	this->SetHealth( healthmax );
	
}

double Damageable::SetMaxHealth( double amount ){
	if (amount < this->health) {
		this->health = amount;
	}

	this->MaxHealth = amount;
	return this->MaxHealth;
}

double Damageable::SetHealth( double amount ){
	this->health = amount;
	return this->health;
}

double Damageable::GetHealth() {
	return this->health;
}

double Damageable::GetMaxHealth() {
	return this->MaxHealth;
}


void Damageable::DoDamage( double amount ) {
	this->health -= amount;
	if (this->health < 0) {
		this->health = 0;
	}
}

double Damageable::DoHeal( double amount ) {
	this->health += amount;
	if (this->health > this->MaxHealth) {
		this->health = this->MaxHealth;
	}

	return health;
}


 

