//------------------------------------------------------------------------------
//
//  Description: This file contains the timer interrupt code
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
extern volatile unsigned int counter;
extern volatile unsigned int count;
extern volatile unsigned char update_display;

volatile unsigned int count2;
extern volatile unsigned int count3;

extern volatile unsigned int SW1check;
extern volatile unsigned int SW2check;

extern volatile unsigned int count_debounce_SW1;
extern volatile unsigned int count_debounce_SW2;
extern volatile unsigned int enable_start;
extern volatile unsigned int flag200ms;
volatile unsigned int timer50ms = 0;
volatile unsigned int circletimer = 0;
extern volatile unsigned int cycle_time;


void Init_Timers(void) {
 Init_Timer_B0();
 Init_Timer_B3();
}

//------------------------------------------------------------------------------
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
  TB0CTL = SETLOW;
  TB0EX0 = SETLOW;
  TB0CTL = TBSSEL__SMCLK; // SMCLK source
  //TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS; // Continuous up
  TB0CTL |= ID__8; // Divide clock by 2
  TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
  TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 &= ~CCIFG;  //clears interrupt flag
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  
   TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
   TB0CCTL1 &= ~CCIFG;  //added in and removed comment from line above and below
   TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  TB0CCTL2 &= ~CCIFG; //clear flag   
  TB0CCTL2 |= CCIE; // CCR2 enable interrupt
  
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
  
  
}
//----


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
  //everytime counter hits 2 one second has passed
  
  if(counter == SECOND){
    counter = RESET;
    count++; // =1second
    count2++;
    count3++;
  
  }
  
  counter++;
 
timer50ms++;          //500ms timer
circletimer++;
  TB0CCR0 += TB0CCR0_INTERVAL;
  
}
  
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,STATE14)){
case RESET: break; // No interrupt
case STATE1: break;
case STATE2: 
  
  ADCCTL0 |= ADCSC; // Start next sample
  TB0CCR1 += adcinterval;
break;
case STATE4: // CCR2 not used
update_display = SETHI;
flag200ms = SETHI;
cycle_time++;
TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
break;
case STATE14: // overflow

break;
default: break;
}
//----------------------------------------------------------------------------
}

void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 R_FORWARD
// TB3.2 P6.1 R_REVERSE
// TB3.3 P6.2 L_FORWARD
// TB3.4 P6.3 L_REVERSE
//------------------------------------------------------------------------------
  TB3CTL = TBSSEL__SMCLK; // SMCLK
  TB3CTL |= MC__UP; // Up Mode
  TB3CTL |= TBCLR; // Clear TAR
  
  TB3CCR0 = WHEEL_PERIOD; // PWM Period
  
  TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
  
  TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.1 Right Reverse PWM duty cycle
  
  TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.2 Left Forward PWM duty cycle
  
  TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}

