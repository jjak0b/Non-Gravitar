#pragma once

#include "Entity.hpp"
#include "Projectile.hpp"
#include "Fuel.hpp"
#include "Point2D.hpp"

#include <list>
using namespace std;

class GameEngine;
class Player;

class Level : public Entity{
protected:
	unsigned int width, height; // dimensioni del mondo
	Entity *StaticEnts; // Entità statiche del mondo ( Bunker, carburante )
	// List *DynamicEnts // Entità dinamiche del mondo ( Proiettili, etc... )
	Player *player; // il giocatore dovrebbe essere tra le StaticEnts ? ( per esempio in StaticEnts[0] )
	// List *WorldPoints // lista dei Point2D che costruiscono il terreno
	list<Projectile*> projectiles;
	char lastInput;

	list<Fuel*> fuel;
	

public:
	/**
	 * @brief Istanzia tutte le entità nel mondo, genera il terreno e le
	 * 
	 */
	Level( unsigned int MaxWidth, unsigned int MaxHeight, Player *player );
	void Update( GameEngine *game );
	void Draw( ViewPort* view );
	Point2D GetNormalizedPoint( Point2D origin );
	void SetOrigin(); // TODO: ovverride perchè non deve fare niente
	// Point2D GetOrigin(); // restituirà (0,0)

	/**
	 * @brief Restituisce la dimensione massima del mondo nell'asse X
	 * @return unsigned int 
	 */
	unsigned int GetMaxWidth();
	/**
	 * @brief Restituisce la dimensione massima del mondo nell'asse Y
	 * @return unsigned int 
	 */
	unsigned int GetMaxHeight();

	/**
	 * @brief Restituisce il puntatore al giocatore
	 * 
	 * @return Player* 
	 */
	Player *GetPlayer();
	void addProjectile(bool shoot);
	void removeProjectile();
	void checkLastInput( GameEngine* game);
	void addFuel(int n25, int n50);
};