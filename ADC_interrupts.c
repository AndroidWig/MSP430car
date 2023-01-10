//------------------------------------------------------------------------------
//
//  Description: This file contains the adc interrupt code
//
//
//  Jason Robinson
//  August 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------


#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>
#include "ports.h"

unsigned int ADC_Channel;
unsigned int ADC_Thumb_Detect;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int hex_value;
char adc_char[]="         ";
extern char *display[DISPARR];
extern char display_line[DISPARR][DISPLINEARR];
extern volatile unsigned char display_changed;
char linechoice = SETLOW;
char locationchoice = FOUR;
unsigned int LEFT_DETECT;
unsigned int RIGHT_DETECT;
int adcj = SETLOW;


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
                          // before its previous conversion result was read.
      break;
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
      break;
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
      break;
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC; // Disable ENC bit.
      switch (ADC_Channel++){
        case RESET: // Channel A5 Interrupt
          
          ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
          ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
          ADC_Thumb_Detect = ADCMEM0; // Move result into Global
          ADC_Thumb_Detect = ADC_Thumb_Detect >> THIRD; // Divide the result by 8 (this one is resolution for thumb wheel
          linechoice = FOUR;
          P2OUT |= IR_LED;

          break;
        case STATE1:
          ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
          ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
          ADC_Left_Detect = ADCMEM0; // Move result into Global
          ADC_Left_Detect = ADC_Left_Detect >> TWO; // Divide the result by 4
          LEFT_DETECT = ADC_Left_Detect;
          linechoice = THIRD;
          break;
        case STATE2:
          ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
          ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
          ADC_Right_Detect = ADCMEM0; // Move result into Global
          ADC_Right_Detect = ADC_Right_Detect >> TWO; // Divide the result by 4 (cuts off numbers that will be oscillating
          RIGHT_DETECT = ADC_Right_Detect;
          linechoice = FOUR;
          P2OUT &= ~IR_LED;
          ADC_Channel=SETLOW;
          break;
default:
break;
}
ADCCTL0 |= ADCENC; // Enable Conversions (must re enable)
//ADCCTL0 |= ADCSC; // Start next sample
// ADC_Thumb = ADCMEM0; // Channel A5
    
      break;
default:
break;
}
}


//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
int i;
void HEXtoBCD(int hex_value){
int value;
for(i=SETLOW; i < FOUR; i++){
adc_char[i] = '0';
}
while (hex_value > NINENINENINE){
hex_value = hex_value - THOUSAND;
value = value + SETHI;
adc_char[SETLOW] = ASCII + value;
}
value = SETLOW;
while (hex_value > NINENINE){
hex_value = hex_value - HUNDRED;
value = value + SETHI;
adc_char[SETHI] = ASCII + value;
}
value = SETLOW;
while (hex_value > NINE){
hex_value = hex_value - TEN;
value = value + SETHI;
adc_char[SECOND] = ASCII + value;
}
adc_char[THIRD] = ASCII + hex_value;
}
//-----------------------------------------------------------------
//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
//-------------------------------------------------------------
int i;
unsigned int real_line;
real_line = line - SETHI;

for(i=RESET; i < FOUR; i++) {

display_line[real_line][i+location] = adc_char[i];
}
}
//-------------------------------------------------------------