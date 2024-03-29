#pragma once

#define FPS_LIMIT 60
#define FRAME_TIME (1.0 / FPS_LIMIT)

#define INPUT_CODE_ESC_KEY_UP 'A'
#define INPUT_CODE_ESC_KEY_DOWN 'B'
#define INPUT_CODE_ESC_KEY_RIGHT 'C'
#define INPUT_CODE_ESC_KEY_LEFT 'D'

#define INPUT_CODE_KEY_PREARROW ((char)224)
#define INPUT_CODE_KEY_UP ((char)72)
#define INPUT_CODE_KEY_DOWN ((char)80)
#define INPUT_CODE_KEY_RIGHT ((char)77)
#define INPUT_CODE_KEY_LEFT ((char)75)

typedef char INPUT_TYPE; // nel caso venga cambiata la definizione in una più complessa, questo equivale ad un refactor.
// tasti relativi ai comandi di gioco
#define INPUT_MOVE_UP 'w'
#define INPUT_MOVE_DOWN 's'
#define INPUT_MOVE_LEFT 'a'
#define INPUT_MOVE_RIGHT 'd'
#define INPUT_USE_FIRE 'f'
#define INPUT_USE_BEAM 'r'


#define ENABLE_COLLISION_ENTITIES
#define ENABLE_COLLISION_LEVEL

// #define DEBUG
#ifdef DEBUG

// #define DEBUG_LEVEL_GENERATION // se attivo genera il terreno in base alla DEBUG_VIEW_DISTANCE
#ifdef DEBUG_LEVEL_GENERATION
#define DEBUG_LEVEL_VIEW_DISTANCE 0.5 // in % quindi se 1.0 equivale alla VIEW_DISTANCE DI DEFAULT
#endif

// #define DEBUG_SURFACE_TERRAIN
// #define DEBUG_COLLISION_DRAWING


#ifdef ENABLE_COLLISION_LEVEL
#define DEBUG_COLLISION_SURFACE_TERRAIN
#endif

#ifdef ENABLE_COLLISION_ENTITIES
#define DEBUG_COLLISION_ENTITIES
#endif

#define DEBUG_TERMINAL_LINES 8

#endif

#define _DEFAULT_WINDOW_HEIGHT 30
#define _DEFAULT_WINDOW_WIDTH 120
#define DEFAULT_WINDOW_HEIGHT (_DEFAULT_WINDOW_HEIGHT)
#define DEFAULT_WINDOW_EXTRA_WIDTH 1 // utilizzato per caratteri speciali quali \n, \0,...
#define DEFAULT_WINDOW_WIDTH (_DEFAULT_WINDOW_WIDTH - DEFAULT_WINDOW_EXTRA_WIDTH)

#define DEFAULT_VIEWPORT_HEIGHT (DEFAULT_WINDOW_HEIGHT*2)
#define DEFAULT_VIEWPORT_WIDTH (DEFAULT_WINDOW_WIDTH)

#define _USE_MATH_DEFINES

#define ENABLE_ANSI_IF_SUPPORTED