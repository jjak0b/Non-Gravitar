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

#define DEBUG
#define _DEFAULT_WINDOW_HEIGHT 30
#define _DEFAULT_WINDOW_WIDTH 120
#define DEFAULT_WINDOW_HEIGHT (_DEFAULT_WINDOW_HEIGHT)
#define DEFAULT_WINDOW_EXTRA_WIDTH 1 // utilizzato per caratteri speciali quali \n, \0,...
#define DEFAULT_WINDOW_WIDTH (_DEFAULT_WINDOW_WIDTH - DEFAULT_WINDOW_EXTRA_WIDTH)

#define DEFAULT_VIEWPORT_HEIGHT (DEFAULT_WINDOW_HEIGHT*2)
#define DEFAULT_VIEWPORT_WIDTH (DEFAULT_WINDOW_WIDTH)

#define _USE_MATH_DEFINES

// #define ENABLE_ANSI_IF_SUPPORTED