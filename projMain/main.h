#ifndef MAIN_H
#define MAIN_H

// Direction definitions
#define DIR_UP     0
#define DIR_RIGHT  1
#define DIR_DOWN   2
#define DIR_LEFT   3

// Screen dimensions
#define screenWidth 128
#define screenHeight 160

// Switch definitions
#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15

// Game constants
#define MOVE_STEP 5
#define WDT_THRESHOLD 25

// External variables (shared across multiple files)
extern int isGameOver;
extern int redrawFlag;
extern int centerCol;
extern int centerRow;
extern int prevCol;
extern int prevRow;
extern int currDirection;
extern unsigned char switches;

extern int squareCol;
extern int squareRow;

// Function prototypes
void update_position();
void gameOver();
void draw_shape(int color);
void update_shape();
void erase_shape();
void wdt_c_handler();
void __interrupt_vec(PORT2_VECTOR) Port_2();

#endif // MAIN_H
