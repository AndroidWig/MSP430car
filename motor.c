//------------------------------------------------------------------------------
//
//  Description: This file contains the movement code
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

extern volatile unsigned int Last_Time_Sequence;  // a variable to identify Time_Sequence has changed
extern volatile unsigned int cycle_time; // is a new time base used to control making shapes
extern volatile unsigned int time_change;        // is an identifier that a change has occurred

 volatile unsigned int right_motor_count;
 volatile unsigned int left_motor_count;

 volatile unsigned int delay_start;

 volatile unsigned int segment_count;
 volatile unsigned int state = WAIT;
 extern volatile char event;
 unsigned int RS = FIVE;
 unsigned int LS = FIVE;
 unsigned int Tot = FIVE;
 int flagcount = SETLOW;
 int count1 = SETLOW;
 int runcount = SETLOW;
 extern volatile unsigned int timer50ms;
 extern unsigned int movetimeint;

void motorstop(void){
 // P6OUT &= ~L_FORWARD; // Set Port pin Low [Wheel Off]
 // P6OUT &= ~R_FORWARD; // Set Port pin Low [Wheel Off]
 // P6OUT &= ~L_REVERSE; // Set Port pin Low [Wheel Off]
 // P6OUT &= ~R_REVERSE; // Set Port pin Low [Wheel Off]
  RIGHT_FORWARD_SPEED = MOTOR_LO;
  LEFT_FORWARD_SPEED = MOTOR_LO;
}

void motorfwd(void){
  //P6OUT |= L_FORWARD; // Set Port pin High [Wheel On]
  //P6OUT |= R_FORWARD; // Set Port pin High [Wheel On]
  RIGHT_FORWARD_SPEED = MOTOR_FAST;
  LEFT_FORWARD_SPEED = MOTOR_FAST;
}


void run_case(unsigned int LS, unsigned int RS, unsigned int Tot, unsigned int movementtime){     //changed def to include cycle time for project 9
  for(timer50ms = RESET;timer50ms<movementtime;timer50ms = timer50ms){
 RIGHT_FORWARD_SPEED = RS;
 LEFT_FORWARD_SPEED = LS;
 
  }
  motorstop();
 
}




