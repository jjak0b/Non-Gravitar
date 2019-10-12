#pragma once

#include "shared/Point2D.hpp"
#include "PrintableBitmap.hpp"

#define CHAR_PIXEL_EMPTY ((char)32) // ' '
#define CHAR_PIXEL_UP ((char)223) // '▀'
#define CHAR_PIXEL_DOWN ((char)220) // '▄'
#define CHAR_PIXEL_UP_DOWN ((char)219) // '█'
#define IS_PIXEL_DATA( value ) ((value) == CHAR_PIXEL_UP || (value) == CHAR_PIXEL_DOWN )

class Level;

/**
 * @brief Classe utilizzata per la gestione della viewport o schermata di gioco.
 * In particolare questa viewport farà riferimento alle seguenti termini:
 * View point: i metodi fanno riferimento alle coordinate positive dei punti nel I° quadrante del piano cartesiano
 * 
 * Bitmap point: i metodi fanno riferimento alle coordinate o indici di una matrice W x H indicizzate da 0 a W-1 e H-1 contenente i Pixel (in realtà caratteri ) ovvero i dati delle "immagini" create in codice ASCII
 * 
 * BitmapData: Generico carattere e quindi dato utilizzabile nella bitmap 
 * 
 * Pixel: Finto Pixel simulato nel terminale, in particolare questa classe considera per Pixel i caratteri '▀', '▄' rispettivamente nominati CHAR_PIXEL_UP e CHAR_PIXEL_DOWN,
 * in modo da poter ottenere delle immagini arcade utilizzando 2 pixel per ogni coordinata delle ordinate; ovvero ogni riga del terminale sarà considerata "virtualmente" come due ordinate indipendenti del piano cartesiano
 * Per esempio posso ottenere questa "Bitmap:" \▄▀▄/ avente in ordinata 0: "▄ ▄" e in ordinata 1 " ▀ " (attenzione: ho scritto coordinate, non indici della bitmap !)
 * che verrà stampata in un' unica riga del terminale, ma una volta caricata in questa Viewport sarà come se fosse di due ordinate.
 * I caratteri non considerati Pixel, saranno considerati come caricati nella ordinata inferiore; infati:
 * 1) SetBitmapdata( '@', (1,0) ) imposterà " @"
 * 2) SetBitmapdata( '@', (1,1) ) imposterà " @"
 * 3) GetBitMapData( ... ) restituirà '@' per il caso (1) e (2) per entrambi le coordinate
 * 4) SetPixel( (0,1) ) imposterà un '▀'; 
 * 5) SetPixel( (0,0) ) imposterà un '▄'; 
 * 6) (4) e (5) imposterà '█' in modo da mostrare interamente i due pixel, ma in realtà se un pixel superiore sarebbe sovrascritto su uno inferiore o viceversa sarà sostituito con un full pixel
 * 
 * 
 * Si vuole mostare un esempio grafico:
 * La prima e seconda ordinata di ogni riga corrispondono al pixel inferiore e superiore rispettivamente
 * 01|       W  
 * 89|   HELLO  
 * 67|       R  
 * 45|  \ /  L █
 * 23|  ▄▀▄  D █
 * 01|▄▀   ▀▄▄▄█
 *   +==========
 *    0123456789
 */
class ViewPort{
protected:
	Point2D world_origin; // posizione relativa al mondo dalla quale mostra gli elementi del livello a seguire
	Vector bounds; // dimensioni della schermata viewport
	PrintableBitmap *data; // "Memoria video" aggiornata frame dopo frame

public:
	ViewPort( unsigned int width, unsigned int height, Point2D origin );

	~ViewPort();

	/**
	 * @brief Aggiunge alla memoria video la texture fornita, in base alla coordinata di world_origin del livello fornita.
	 * In particolare la texture verrà disegnata in modo che world_origin sarà la coordinata centrale in basso della texture
	 * 
	 * @param texture 
	 * @param level 
	 * @param world_origin 
	 */
	void Draw( Bitmap *texture, Level *level, Point2D world_origin );

	/**
	 * @brief Ripristina la "memoria video" impostandola a valori = CHAR_PIXEL_EMPTY
	 * 
	 */
	void Clear();

	/**
	 * @brief Aggiorna il contenuto della viewport, mostrandola nel livello di output dal terminale
	 * 
	 */
	void Refresh();

	/**
	 * @brief Aggiorna la dimensione della memoria video allocata, se le dimensioni fornite sono diverse da quelle attuali
	 * PostCondition: il contenuto della memoria video non è significativo
	 * @param width 
	 * @param height 
	 * @return true se la dimensione è stata aggiornata
	 * @return false altrimenti se è rimasta invariata
	 */
	bool UpdateSize( unsigned int width, unsigned int height );

	/**
	 * @brief Stampa del testo sulla Schermata di gioco ("simula una specie di HUD") in uno specifico punto,
	 * Ad ogni occorenza di '\n' continua a stampare nella riga successiva ma nella stessa ascisse di view_point.
	 * PreCondition: il punto è locale relativo alla viewport, cioè prendendo in consideraione il punto nel primo quadrante del piano cartesiano;
	 * str_text deve essere una stringa
	 * PostCondition: Se a partire dal view_point fornito, alcune lettere sarebbero stampate oltre il limite width della viewport,
	 * tali saranno spostate invece all'inizio della riga successiva ( come se ci fosse un '\n' ), mantenendo sempre la prima lettere di ogni riga nella medesima coordinata x di view_point
	 * @param str_text 
	 * @param view_point punto da dove iniziare a stampare
	 * @param color colore del testo
	 */
	void Print( const char str_text[], Point2D view_point, Color);

	/**
	 * @brief Restituisce il punto della viewport relative al punto del livello
	 * @param world 
	 * @param world_point 
	 * @return Point2D 
	 */
	Point2D WorldPointToViewPoint( Level *world, Point2D world_point );

	/**
	 * @brief Restituisce la larghezza attuale di questo oggetto
	 * @return unsigned int 
	 */
	unsigned int GetWidth();

	/**
	 * @brief Restituisce l'altezza attuale di questo oggetto
	 * @return unsigned int 
	 */
	unsigned int GetHeight();

	/**
	 * @brief Imposta il punto del mondo dal quale la viewport deve mostrare il mondo, in particolare il punto in basso a sinistra (bottom-left) del mondo dal quale verranno mostrati i pixel impostati a seguire in larghezza ed in altezza
	 * PreCondition: Deve essere richiamata prima di effettuare qualsiasi operazione di Draw(...), SetPixel(...), Copy(...), etc...
	 * @param WorldOrigin 
	 */
	void SetWorldOrigin( Point2D WorldOrigin );

		/**
	 * @brief Disegna nella ViewPort un linea a partire da start fino a end, dove start e end sono coordinate del mondo
	 * @param view
	 * @param world
	 * @param start
	 * @param end
	 */
	void DrawLine( Level *world, Point2D start, Point2D end, Color color );

	/**
	 * @brief Disegna nella Viewport un cerchio con centro le coordinate dell'origine, e raggio specificati
	 *
	 * @param view
	 * @param world
	 * @param world_origin
	 * @param radius
	 */
	void DrawCircle( Level *world, Point2D world_origin, double radius, Color color );

	protected:

	/**
	 * @brief dealloca le risorse di data
	 * 
	 */
	void Dispose();
};

/**
 * @brief Converte le coordinate locali relative alla viewport nelle corrispondenti relative alla bitmap specificata
 * @param view_point 
 * @param bitmap 
 * @return Point2D 
 */
Point2D ViewPointToBitMapPoint( Point2D view_point, Bitmap *bitmap );

/**
 * @brief Restituisce il valore attuale nella Viewport al punto specificato
 * PreCondition: il punto è locale relativo alla viewport, cioè prendendo in consideraione il punto nel primo quadrante del piano cartesiano
 * @param view_point
 * @return BITMAP_DATA_TYPE
 */
BITMAP_DATA_TYPE GetBitmapData( Bitmap* bitmap, Point2D view_point );

/**
 * @brief Imposta il "valore" del pixel nel punto specificato relativo alla viewport
 * PreCondition: il punto è locale relativo alla viewport, cioè prendendo in consideraione il punto nel primo quadrante del piano cartesiano
 * PostCondition: se value è CHAR_PIXEL_UP o CHAR_PIXEL_DOWN verrà automaticamente adattato alla viewport tramite SetPixel( ... )
 * @param value
 * @param view_point
 * @return true
 * @return false
 */
bool SetBitmapData( Bitmap* bitmap, BITMAP_DATA_TYPE value, Color color, Point2D view_point );

/**
 * @brief Imposta il pixel al punto specificato relativo alla viewport
 * PreCondition: il punto è locale relativo alla viewport, cioè prendendo in consideraione il punto nel primo quadrante del piano cartesiano
 * @param view_point
 * @return true se il pixel è stato impostato nel punto fornito
 * @return false altrimenti ( il punto non è interno alla viewport )
 */
bool SetPixel( Bitmap* bitmap,  Point2D view_point, Color color );

/**
 * @brief Disegna un cerchio aventi certe caratteristiche nella bitmap fornita;
 * @PostCondition Se bitmap == NULL allora sarà allocata una nuova bitmap, di dimensione 2*radius x 2*radius, necessaria
 * all'operazione
 * @param bitmap
 * @param centre_view_point : centro del cerchio, se bitmap == NULL, allora sarà considerata al centro della bitmap creata
 * @param radius
 * @param color
 * @return il puntatore della bitmap su cui si è effettuata l'operazione
 */
Bitmap* PaintCircleIntoBitmap( Bitmap* bitmap, Point2D centre_view_point, const unsigned int radius, const Color color );