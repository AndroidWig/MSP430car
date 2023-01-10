//------------------------------------------------------------------------------
//
//  Description: This file contains the code for the switches
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

volatile unsigned int okay_to_look_at_switch1;
volatile unsigned int sw1_position;
volatile unsigned int count_debounce_SW1 = SETLOW;
volatile unsigned int DEBOUNCE_TIME;
volatile unsigned int okay_to_look_at_switch2;
volatile unsigned int sw2_position;
volatile unsigned int count_debounce_SW2=SETLOW;
volatile unsigned int SW1check = SETLOW;
volatile unsigned int SW2check = SETLOW;
extern volatile char event;
extern volatile unsigned int state;
unsigned int swtimer = SETLOW;
extern volatile unsigned int count2;
extern volatile unsigned int count3;
volatile unsigned int enable_start = SETLOW;
extern volatile unsigned int SW1main;
extern volatile unsigned int SW2main;
extern unsigned int flipflag;
extern volatile unsigned char display_changed;

#pragma vector=PORT4_VECTOR
__interrupt void switch1(void){
  if(P4IFG & SW1){
    P4IFG &= ~SW1;
    
    SW1check = SETHI;
    SW1main = SETHI;
    count3 = SETLOW;
    count_debounce_SW1 = SETLOW;
    P4IE &= ~SW1;
   
    
    TB0CCR1 = TB0R + TB0CCR1_INTERVAL; //set ccr1 to initaial valu0e
    TB0CCTL1 &= ~CCIFG; //clears interrupts flag
    TB0CCTL1 |= CCIE;   //ccr1 enable interrupt
    
    //P1OUT ^= RED_LED;
    P6OUT ^= GRN_LED;
    enable_start = SETHI;
        count2 = SETLOW;
    
   
    TB0CCTL0 &= ~CCIE;  //disables interrupts for ccr0
    P6OUT &= ~LCD_BACKLITE;     //turns off display
  }
}
    
#pragma vector=PORT2_VECTOR
__interrupt void switch2(void){
  if(P2IFG & SW2){
    P2IFG &= ~SW2;
    
    SW2check = SETHI;
    SW2main = SETHI;
    count3 = SETLOW;
    count_debounce_SW2 = SETLOW;
    P2IE &= ~SW2;
    
    if(flipflag){               //flips between baud rates
      //set_baud_two();
      disprate2();
    }
    else{
      set_baud_one();
      disprate1();
    }
    display_changed = SETHI;
    
    
    TB0CCR1 = TB0R + TB0CCR1_INTERVAL; //set ccr1 to initaial valu0e TB0R is to enable interrupt not running from start
    TB0CCTL1 &= ~CCIFG; //clears interrupts flag
    TB0CCTL1 |= CCIE;   //ccr1 enable interrupt
    
    
    
      swtimer++;
    
    TB0CCTL0 &= ~CCIE;  //disables interrupts for ccr0
    P6OUT &= ~LCD_BACKLITE;     //turns off display
  }
}  
  