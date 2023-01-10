//------------------------------------------------------------------------------
//
//  Description: This file contains the code for serial transmit and recieve
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "msp430fr2355.h"
#include  "functions.h"
#include  "macros.h"
#include  <string.h>

// Ring buffers for UCA0 (IOT)
volatile char iot_recieve[RING_SIZE];   // Receive ring buffer 
volatile unsigned int iot_rx_write;   // iot rx write index
volatile unsigned int iot_rx_read;   // iot rx read index
volatile char iot_transmit[RING_SIZE];   // Transmit ring buffer
volatile unsigned int iot_tx_write;   // iot tx write index 
volatile unsigned int iot_tx_read;   // iot tx read index
volatile unsigned int direct_iot = SETLOW;           //from carlsons code added in project 9

// Ring buffers for UCA1 (PC/USB)
volatile char usb_recieve[RING_SIZE];   // Receive ring buffer 
volatile unsigned int usb_rx_write;   // usb rx write index 
volatile unsigned int usb_rx_read;   // usb rx read index 
volatile char usb_transmit[RING_SIZE];   // Transmit ring buffer
volatile unsigned int usb_tx_write;   // usb tx write index 
volatile unsigned int usb_tx_read;   // usb tx read index
volatile unsigned int transmitflag = SETLOW;
volatile char tempchar[RING_SIZE];
unsigned int temporary;
unsigned int globaltoggle = SETLOW;
 char loopback[RING_SIZE];      //string to be sent to the other isr
 char loopbackfeed[RING_SIZE];
volatile char IOT_RING_RX[RING_SIZE];
extern volatile unsigned int iot_tx;

int tempwrite;
 int tempdirect;
 
 //project 09 variables
volatile char RxBUFF[prolim][RING_SIZE];
volatile unsigned int top = SETLOW;
volatile unsigned int Rx = SETLOW;
extern volatile unsigned int Setup_transfer_size;
unsigned int setuptemp;
extern char iot_transmit1[RING_SIZE];
extern volatile unsigned int startflg;


char ncsu_string[11]; //ncsu #1 string to send

// Configuration for UCA0
void Init_Serial_UCA0(void){    // Initialize UCA0 for IOT
  int i;
  for(i=RESET; i<RING_SIZE; i++){
    iot_recieve[i] = SETLOW;      // IOT Rx ring buffer
  }
  iot_rx_write = BEGINNING;   // write/read index set to zero 
  iot_rx_read = BEGINNING;
  
  for(i=RESET; i<RING_SIZE; i++){  // May not use this
    iot_transmit[i] = SETLOW;      // IOT Tx ring buffer
  }
  iot_tx_write = BEGINNING;   // write/read index set to zero 
  iot_tx_read = BEGINNING; 
  
  // Configure UART 0 
  UCA0CTLW0 = RESET;          // Use word register
  UCA0CTLW0 |= UCSWRST;       // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as f_BRCLK
  
 
  UCA0BRW = UCBRx_BAUD_1;  // INT(69.444/16) = 4 for 115200 baud
 
  UCA0MCTLW = BITCLK_BAUD_1;        
  UCA0CTLW0 &= ~UCSWRST;  // Set software reset enable
  UCA0IE |= UCRXIE;       // Enable RX interrupt UCA0
  
 
}

// Configuration for UCA1 (PC/USB)
void Init_Serial_UCA1(void){    // Initialize UCA1 for PC/USB
  //------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
  
  int i;
  for(i=RESET; i<RING_SIZE; i++){
    usb_recieve[i] = SETLOW;      // PC/USB Rx ring buffer
  }
  usb_rx_write = BEGINNING;   // write/read index set to zero 
  usb_rx_read = BEGINNING;
  
  for(i=RESET; i<RING_SIZE; i++){  // May not use this
    usb_transmit[i] = SETLOW;      // PC/USB Tx ring buffer
  }
  usb_tx_write = BEGINNING;   // write/read index set to zero 
  usb_tx_read = BEGINNING; 
  
  // Configure UART 1
  UCA1CTLW0 = RESET;          // Use word register
  UCA1CTLW0 |= UCSWRST;       // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as f_BRCLK
  
  
  UCA1BRW = UCBRx_BAUD_1;  // INT(69.444/16) = 4 for 115200 baud
 
  UCA1MCTLW = BITCLK_BAUD_1;        
  UCA1CTLW0 &= ~UCSWRST;  // Set software reset enable
  UCA1IE |= UCRXIE;       // Enable RX interrupt UCA1
  
  
}

// Interrupt for UCA0 (IOT)
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp;
  unsigned int temp1;
  unsigned int temp2;
  
  switch(__even_in_range(UCA0IV,SERIAL_FLAGS)){
    case VECTOR_0: // Vector 0 - no interrupt
      break;
    case RXIFG: // Vector 2 - RXIFG
      
      temp = UCA0RXBUF;
      UCA1TXBUF = temp;
      temp = Rx++;
      
      temp1 = UCA0RXBUF;
      
      
      RxBUFF[top][temp] = temp1;
      if(UCA0RXBUF == MAX){ //newline check
        Rx = RESET;
        top++;
        if(top >= prolim){
          top = RESET;
        }
      }
      
      iot_recieve[iot_rx_write++] = temp; // Add to Ring Buffer
      if(iot_rx_write >= sizeof(iot_recieve)){
        iot_rx_write = BEGINNING;
      }
   
      
      break;
    case TXIFG: // Vector 4 – TXIFG
      
      temp2 = iot_rx_read++;
      UCA0TXBUF = iot_transmit1[temp2];
      setuptemp = Setup_transfer_size;
      if(iot_rx_read > setuptemp){      //setup transfer size is passed in variable with size of string
        startflg++;
        UCA0IE &= ~UCTXIE;
      }
     
      break;
  default: break; 
  }
}

// Interrupt for UCA1 (PC/USB)
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA1IV,SERIAL_FLAGS)){
    case VECTOR_0: // Vector 0 - no interrupt
      break;
    case RXIFG: // Vector 2 - RXIFG
      
      
      temp = UCA1RXBUF;
      UCA0TXBUF = temp;
     
  
      break;
    case TXIFG: // Vector 4 – TXIFG
      
      
      UCA1TXBUF = iot_recieve[direct_iot++];
      
      if(direct_iot >= sizeof(iot_recieve)){
        direct_iot = BEGINNING;
      }
      tempwrite = iot_rx_write;
      tempdirect = direct_iot;
      if(tempwrite == tempdirect){
        UCA1IE &= ~UCTXIE;
      }

      
      break;
  default: break; 
  }
}


// Functions to set baud rate 
void set_baud_one(void){  // Sets baud rate 115,200 for UCA0 and UCA1
  
  // Reconfigure UART0
  UCA0CTLW0 = RESET;          // Use word register
  UCA0CTLW0 |= UCSWRST;       // eUSCI_A0 held in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as f_BRCLK
  
  // Reconfigure UART1
  UCA1CTLW0 = RESET;          // Use word register
  UCA1CTLW0 |= UCSWRST;       // eUSCI_A1 held in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as f_BRCLK
  
  // Baudrate 115200:
  // N = 69.444   UCBRx = 4    OS16 = 1
  // UCBRFx = 5   UCBRSx = 0.44444 = 0x55 from table
  UCA0BRW = UCBRx_BAUD_1;  // INT(69.444/16) = 4 for 115200 baud
  UCA1BRW = UCBRx_BAUD_1;  // INT(69.444/16) = 4 for 115200 baud
  // UCAxMCTLW = UCBRSx concatenate UCBRFx concatenate UCOS16
  // UCAxMCTLW = 0x55 concatenate 5 concatenate 1
  UCA0MCTLW = BITCLK_BAUD_1;    // MCTLW bits 15-8 for BITCLK  
  UCA1MCTLW = BITCLK_BAUD_1;    // MCTLW bits 7-4 for modulation patter with UCOS16 = 1
  UCA0CTLW0 &= ~UCSWRST;  // eUSCI_A0 reset released for operation
  UCA1CTLW0 &= ~UCSWRST;  // eUSCI_A1 reset released for operation
  UCA0IE |= UCRXIE;       // Enable RX interrupt UCA0
  UCA1IE |= UCRXIE;       // Enable RX interrupt UCA1
  // UCA0IE |= UCTXIE;       // Enable TX interrupt UCA0
  // UCA1IE |= UCTXIE;       // Enable TX interrupt UCA1

}

 




void clear_ring_buffs(void){
  int i;
  for(i=RESET; i<RING_SIZE; i++){
    iot_recieve[i] = SETLOW;      // IOT Rx ring buffer
  }
  iot_rx_write = BEGINNING;   // write/read index set to zero 
  iot_rx_read = BEGINNING;
  
  for(i=RESET; i<RING_SIZE; i++){  // May not use this
    iot_transmit[i] = SETLOW;      // IOT Tx ring buffer
  }
  iot_tx_write = BEGINNING;   // write/read index set to zero 
  iot_tx_read = BEGINNING; 
  
  for(i=RESET; i<RING_SIZE; i++){
    usb_recieve[i] = SETLOW;      // PC/USB Rx ring buffer
  }
  usb_rx_write = BEGINNING;   // write/read index set to zero 
  usb_rx_read = BEGINNING;
  
  for(i=RESET; i<RING_SIZE; i++){  // May not use this
    usb_transmit[i] = SETLOW;      // PC/USB Tx ring buffer
  }
  usb_tx_write = BEGINNING;   // write/read index set to zero 
  usb_tx_read = BEGINNING; 
}
void initserial(void){
    Init_Serial_UCA0();
    Init_Serial_UCA1();
    globaltoggle = SETLOW;
}