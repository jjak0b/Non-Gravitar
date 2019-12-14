#pragma once
#include "Segment.hpp"
#include <list>
using namespace std;

class Level;

#ifdef DEBUG_COLLISION_DRAWING
class GameEngine;
#endif
enum ShapeAddOffsetOption {
	ADD_FRONT = 0,
	ADD_BACK = 1
};

/**
 * @brief Classe rappresentante una figura geometrica costituita da vertici.
 * 
 */
class Shape{

    protected:
		/**
		 * @brief ultima posizione aggiornata della figura,
		 * ad ogni UpdateAbsolute è aggiornata.
		 * Utilizzata per tenere traccia dell'ultima origine presa in considerazione in UpdateAbsolute
		 */
		Point2D last_origin;

		/**
		 * @brief lista di vertici con coordinate assolute della figura
		 * rispetto alla sua origine del livello
		 * aggiornati tramite UpdateAbsolutes, ed utilizzati per evitare un ricalcolo per ulteriori controlli
		 * 
		 */
        list<Point2D> absolute_points;

		/**
		 * @brief lista di vertici con coordinate (offset) relative della figura
		 * rispetto alla posizione centrale della figura stessa
		 * Molto pià significativi rispetto a absolute_points
		 */
        list<Point2D> offset_points;

		/**
		 * @brief punto contenente le coordinate minime del bounding box,
		 * ovvero le coordinate minime di un rettangolo
		 */
		Point2D min_offset = Point2D(0,0);

		/**
		 * @brief punto contenente le coordinate massime del bounding box,
		 * ovvero le coordinate massime di un rettangolo
		 */
		Point2D max_offset = Point2D(0,0);
		
    public:

        Shape();

        virtual ~Shape();

		/**
		 * @brief Aggiunge un punto assoluto alla lista nell'estremo indicato
		 * 
		 * @param point 
		 * @param option 
		 */
        void addAbsolute( Point2D point, ShapeAddOffsetOption option = ADD_FRONT );

		/**
		 * @brief Aggiunge un punto di offset relativo alla posizione e il suo assoluto associato alle liste nel estremo indicato
		 * 
		 * @param point 
		 * @param origin 
		 * @param option 
		 */
        void addOffset( Point2D point, Point2D origin, ShapeAddOffsetOption option = ADD_FRONT );

		/**
		 * @brief Rimuove l'ultimo offset e il suo punto assoluto associato nell'estremo indicato
		 * 
		 * @param option 
		 * @return Point2D 
		 */
		Point2D PopOffset( ShapeAddOffsetOption option );

		/**
		 * @brief Restituisce il numero di offset memorizzati
		 * 
		 * @return size_t 
		 */
        size_t GetOffsetCount();

		/**
		 * @brief Restituisce la lista dei punti assoluti
		 * 
		 * @return list<Point2D> 
		 */
        list<Point2D> getAbsolutes();

		/**
		 * @brief Restituisce la lista degli offset relativi
		 * 
		 * @return list<Point2D> 
		 */
		list<Point2D> getOffsetPoints();

		/**
		 * @brief Aggiorna tutti i punti assoluti della figura con una somma vettoriale
		 * tra gli offset realtivi e la posizione indicata
		 * 
		 * @param origin 
		 */
		void UpdateAbsolutes( Point2D origin );

		/**
		 * @brief Indica se questo oggetto sta collidendo con un altra Shape
		 * in base alle posizioni delle due figure
		 */
		bool IsShapeColliding(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds );

};