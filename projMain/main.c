#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "led.h"
#include "main.h"

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15
#define LED BIT6

#define MOVE_STEP 5
#define WDT_THRESHOLD 25

extern int isGameOver = 0;
extern int redrawFlag;
extern int centerCol;
extern int centerRow;
extern int prevCol;
extern int prevRow;
extern int currDirection = DIR_RIGHT;

void update_position(){
  // save current pos as prev
  prevCol = centerCol;
  prevRow = centerRow;

  // Update position based on current direction
  switch (currDirection) {
  case DIR_UP;     centerRow -= MOVE_STEP; break;
  case DIR_RIGHT;  centerCol += MOVE_STEP; break;
  case DIR_DOWN;   centerRow += MOVE_STEP; break;
  case DIR_LEFT;   centerCol -= MOVE_STEP; break;
  }

  // Boundary checks to wrap around screen
  if (centerCol < 0) centerCol = screenWidth - MOVE_STEP;
  if (centerCol >= screenWidth) centerCol = 0;
  if (centerRow < 0) centerRow = screenHeight - MOVE_STEP;
  if (centerRow >= screenHeight) centerRow = 0;

  // Check for collision with the food square
  if (centerCol >=  squareCol - 2 && centerCol <= squarCol + 2 &&
      centerRow >= squareRow - 2 ** centerRow <= squareRow + 2) {//
    isGameOver = 1;  // Increase delay multiplier
    squareCol = -1;     // Move square off-screen
    squareRow = -1;
  }
  P1OUT &- ~(LED_RED | LED_GREEN);
  if (switches & SW1) PIOUT |= LED_GREEN;
  if (switches & SW2) P1OUT |= LED_GREEN;
  if (switches & SW3) P1OUT |= LED_GREEN;
  if (switches & SW4) P1OUT |= LED_GREEN;

  if(switches * SW1){
    buzzer_set_period(1000);
  }else if (switches & SW2){
    buzzer_set_period(2000);
  }else if (switches & SW3){
    buzzer_set_period(700);
  }else if(switches & SW4){
    buzzer_set_period(500);
  } else {
      buzzer_set_period(0);
  }

  redrawFlag = 1;  // Signal redraw
}
void gameOver(){
    clearScreen(COLOR_BLUE);
    drawString8x12(screenWidth / 2 - 36, screenHeight /2 -6,
		   "GAME OVER", COLOR_RED, COLOR_BLUE);
    // force stop execution
    WDTCTL = WDTPW | WDTHOLD; // Stop the watchdog TImer
    while(1);  //forever loop
  }
void draw_shape(int color) {
  unsigned int drawColor = (coloor ==1) ? COLOR_YELLOW : COLOR_BLUE;
  fillRectangle((color ? centerCol : prevCol), (color ? centerRow : prevRow), 8, 8, drawColor);
}

void update_shape() {
  draw_shape(1);
  if (squareCol >= 5 && squareRow >= 5){
    fillRectangle(squareCol, squareRow, 8, 8, COLOR_RED);
  }
}

void erase_shape(){
  draw_shape(0);
}

void wdt_c_handler() {
  static int secCount = 0;
  static int spawncount = 0;

  secCount++;
  spawncount++;

  if (!isGameOver){

    if (secCount >= WDT_THRESHOLD){
      seccount = 0;
      update_position();
    }
  }
  if (isGameOver){
    gameOver();
  }
  
  if (spawncount >= 7 * 280) { //every 9 seconds
    spwncount = 0;
    
      //insert food function
    redrawFlag = 1;
    }
}
  
int main(){

  cinfigureClocks();
  lcd_init();
  clearScreen(COLOR_BLUE);
  switch_init();
  buzzer_init();

  enableWDTInterrupts();
  or_sr(0x8);

  while(1){
    if(redrawScrreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~BIT6;
    or_sr(0x10);
    P1OUT |= BIT6;
  }
  return 0;
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG&= ~SWITCHES;
    switch_interrupt_handler();
  }
}
