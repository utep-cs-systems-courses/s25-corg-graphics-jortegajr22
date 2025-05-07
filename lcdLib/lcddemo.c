/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  short rowMiddle = screenHeight/2;
  short colMiddle = screenWidth /2;
  short row  = 0, col = 0;

 
  drawString5x7(20,20, "deez nuts", COLOR_WHITE, COLOR_RED);

  drawString8x12(50, 50, "deez nuts", COLOR_WHITE, COLOR_RED);
  
}
