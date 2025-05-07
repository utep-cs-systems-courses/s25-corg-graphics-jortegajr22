#include <msp430.h>
#include "../timerLib/libTimer.h"
#include "buzzer.h"

void buzzer_init(){
  timerAUpmode();

  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycle){
  CCR0 = cycle;
  CCR1 = cycle >> 1;
}
