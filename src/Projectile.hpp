#pragma once

#include "Entity.hpp"
#include "Point2D.hpp"

class Level;

class Projectile : public Entity{
    protected:
    int type; // entità che ha sparato questo proiettile
    double damage; // danno che infligge a qualsiasi entità che colpisce
    Point2D fireOrigin; // punto di partenza da cui è stato generato il proiettile
    Point2D targetOrigin; // punto destinazione che dovrebbe raggiungere il proiettile
    char lastInput;

    public:
    Projectile( Level *world, Point2D origin, Point2D targetOrigin, double damage, char lastInput);
    
    Point2D GetTargetOrigin();
    double GetDamage();
    bool Update(); // aggiorna lo stato del proiettile, come la posizione, ecc...
    
    void GetTargetOrigin(Point2D target);
    void GetDamage(double damage);
};