//------------------------------------------------------------------------------
//
//  Description: This file contains the code for setting up the optional DAC
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>
unsigned int DAC_data;

void Init_DAC(void){
  
  DAC_data = THOUSAND; // Value between 0x000 and 0x0FFF
  SAC3DAT = DAC_data; // Initial DAC data
  SAC3DAC = DACSREF_1; // Select int Vref as DAC reference
  SAC3DAC |= DACLSEL_0; // DAC latch loads when DACDAT written
  // SAC3DAC |= DACIE; // generate an interrupt
  SAC3DAC |= DACEN; // Enable DAC
  
  SAC3OA = NMUXEN; // SAC Negative input MUX controL
  SAC3OA |= PMUXEN; // SAC Positive input MUX control
  SAC3OA |= PSEL_1; // 12-bit reference DAC source selected
  SAC3OA |= NSEL_1; // Select negative pin input
  SAC3OA |= OAPM; // Select low speed and low power mode
  SAC3PGA = MSEL_1; // Set OA as buffer mode
  SAC3OA |= SACEN; // Enable SAC
  SAC3OA |= OAEN; // Enable OA
}
