//------------------------------------------------------------------------------
//
//  Description: This file contains the initialization code
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include "ports.h"
#include  "functions.h"
#include  "msp430.h"

extern char display_line[DISPARR][DISPLINEARR];
extern char *display[DISPARR];
extern volatile unsigned char update_display;


void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=RESET;i<DISPLINEARR;i++){
    display_line[DISPLINE1][i] = RESET_STATE;
    display_line[DISPLINE2][i] = RESET_STATE;
    display_line[DISPLINE3][i] = RESET_STATE;
    display_line[DISPLINE4][i] = RESET_STATE;
  }
  display_line[DISPLINE1][MAX] = RESET_STATE;
  display_line[DISPLINE2][MAX] = RESET_STATE;
  display_line[DISPLINE3][MAX] = RESET_STATE;
  display_line[DISPLINE4][MAX] = RESET_STATE;

  display[DISPLINE1] = &display_line[DISPLINE1][SETLOW];
  display[DISPLINE2] = &display_line[DISPLINE2][SETLOW];
  display[DISPLINE3] = &display_line[DISPLINE3][SETLOW];
  display[DISPLINE4] = &display_line[DISPLINE4][SETLOW];
  update_display = RESET;


// Interrupts are disabled by default, enable them.
//------------------------------------------------------------------------------
}


void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}