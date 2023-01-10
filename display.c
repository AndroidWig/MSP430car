//------------------------------------------------------------------------------
//
//  Description: This file contains the display functions
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern char *display[DISPARR];
extern char display_line[DISPARR][DISPLINEARR];
extern volatile unsigned char display_changed;
extern volatile unsigned int flag200ms;
extern char count200[];

void count200ms(void){
  if(count200[DECIMAL] != '8') count200[DECIMAL] = count200[DECIMAL] + TWO;
  else if(count200[ONES] != '9') {
    count200[ONES] = count200[ONES] + INCREMENT;
    count200[DECIMAL] = '0';
  }
  
  else if(count200[TENS] != '9') {
    count200[TENS] = count200[TENS] + INCREMENT;
    count200[ONES] = '0';
    count200[DECIMAL] = '0';
  }
  else if(count200[HUNDREDS] != '9') {
    count200[HUNDREDS] = count200[HUNDREDS] + INCREMENT;
    count200[TENS] = '0';
    count200[ONES] = '0';
    count200[DECIMAL] = '0';
  }
  
  strcpy (display_line[DISPLINE4], count200);
}


void dispcirc(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "  Circle  ");
  strcpy(display_line[DISPLINE4], "          ");
}

void disptri(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Triangle ");
  strcpy(display_line[DISPLINE4], "          ");
}

void dispfig8(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Figure 8 ");
  strcpy(display_line[DISPLINE4], "          ");
}

void dispfwd(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "  Forward ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void disprev(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "  Reverse ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispstop(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "   Stop   ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}
void dispcw(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "  Spin CW ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispccw(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Spin CCW ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void sw1press(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " SW1 Press");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void sw2press(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " SW2 Press");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void DISP_BLACK(void){
  
  strcpy(display_line[DISPLINE3], " BLK Line ");
  display_changed = SETHI;
}

void circfin(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "Circle Fin");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispintercept(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "Intercept ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispturn(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Turning  ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispcircling(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Circling ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispstopped(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], " Stopped  ");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void disprefind(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "Re-finding");
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}

void dispbaud(void){

  strcpy(display_line[DISPLINE3], "   Baud   ");
  display_changed = SETHI;
}

void disprate1(void){
  strcpy(display_line[DISPLINE3], "  115200  ");
  display_changed = SETHI;
}
 
void disprate2(void){
  strcpy(display_line[DISPLINE3], "  460800  ");
  display_changed = SETHI;
}

void clear2lines(void){
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  display_changed = SETHI;
}

void dispwait(void){
  strcpy(display_line[DISPLINE1], " WAITING  ");
  display_changed = SETHI;
}

void disptransmit(void){ 
  strcpy(display_line[DISPLINE1], " TRANSMIT ");
  display_changed = SETHI;
}
                     
void dispreceived(void){                    
  strcpy(display_line[DISPLINE1], " RECEIVED ");
  display_changed = SETHI;
}
void clearline1(void){
  strcpy(display_line[DISPLINE1], "          ");
  display_changed = SETHI;
}

void clearline4(void){
  strcpy(display_line[DISPLINE4], "          ");
  display_changed = SETHI;
}