//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>
#include <stdlib.h>


//#define ALWAYS                  (1)
//#define RESET_STATE             (0)
//#define RED_LED              (0x01) // RED LED 0
//#define GRN_LED              (0x40) // GREEN LED 1
//#define TEST_PROBE           (0x01) // 0 TEST PROBE
//#define TRUE                 (0x01) //
//#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
//#define RED_LED                (0x01) // 1.0 RED LED 0
//#define GRN_LED                (0x40) // 6.6 GREEN LED

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Display_Process(void);
void Init_LEDs(void);
void Carlson_StateMachine(void);

// Global Variables
volatile char slow_input_down;
extern char display_line[DISPARR][DISPLINEARR];
extern char *display[DISPARR];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int Last_Time_Sequence;  // a variable to identify Time_Sequence has changed
volatile unsigned int cycle_time; // is a new time base used to control making shapes
volatile unsigned int time_change;        // is an identifier that a change has occurred
volatile char event = CIRCLE;
volatile unsigned int count;
volatile unsigned int counter;
volatile unsigned int flag200ms;
extern char count200[] = "     000.0";
volatile unsigned int SW1main = SETLOW;
volatile unsigned int SW2main = SETLOW;
volatile unsigned int startflg = SETLOW;
unsigned int test;
volatile unsigned int count3 = SETLOW;
char Serial_display_string[LCD_INDEX];
extern volatile char usb_recieve[RING_SIZE];
unsigned int clearflg = SETHI;
unsigned int flipflag = SETLOW;
char teststring[MAX];
extern volatile unsigned int transmitflag;
extern volatile char iot_recieve[RING_SIZE];
extern char ncsu_string[DISPLINEARR];
volatile unsigned int iot_tx = SETLOW;

//project 9 extern variables
extern volatile unsigned int iot_rx_write;
extern volatile unsigned int iot_rx_read;
extern volatile char iot_transmit[RING_SIZE];

unsigned int iot_rx_wr_temp;
unsigned int line=SETLOW;
unsigned int character;
unsigned int nextline;
unsigned int IOT_parse;
volatile char AT[RING_SIZE];
unsigned int boot_state;
volatile char ip_mac[RING_SIZE];
unsigned int ip_address_found;
volatile char ip_address[RING_SIZE];
volatile unsigned int iot_index;
volatile unsigned int test_Value;
unsigned int IOT_Data[FOUR][RING_SIZE];
extern volatile unsigned int iot_tx;

//project 09 variables
extern volatile char RxBUFF[prolim][RING_SIZE];
extern volatile unsigned int top;
extern volatile unsigned int Rx;
char RxBUFFcheck[prolim][RING_SIZE];
volatile unsigned int bottom = SETLOW;
extern volatile unsigned int top;
char iot_transmit1[RING_SIZE];
extern volatile unsigned int  iot_rx_read;
volatile unsigned int Setup_transfer_size = SETLOW;
unsigned int testflag= SETLOW;
char tempip[LCD_INDEX];
char tempip2[LCD_INDEX];
char ssidprint[LCD_INDEX];
unsigned int tempipcount2 = SETLOW;
unsigned int tempipcount = SETLOW;
unsigned int topnonvol; //used to create a non volatile top for comparison
unsigned int mainstate;
unsigned int movetimeint;
volatile unsigned int blacklineflag = SETLOW;
volatile unsigned int autoflagmain = SETLOW;
extern unsigned int LEFT_DETECT;
extern unsigned int RIGHT_DETECT;
unsigned int linefollowflag= SETLOW;
extern volatile unsigned int timer50ms;
unsigned int controldispflag = SETLOW; //flag to stop displaying waiting for input
char movetime[FOUR];
char tempprev[] = " ";
unsigned int oddeven = SETHI;
extern volatile unsigned int circletimer;
unsigned int stopflagfinal = SETLOW;
void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  
  PM5CTL0 &= ~LOCKLPM5;
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  //Init_Switches();
  Init_ADC();
  //Init_DAC();
  initserial();
  
  // Place the contents of what you want on the display, in between the quotes
  // Limited to 10 characters per line
  
  strcpy(display_line[DISPLINE1], "          ");
  strcpy(display_line[DISPLINE2], "          ");
  strcpy(display_line[DISPLINE3], "          ");
  strcpy(display_line[DISPLINE4], "          ");
  
  // This line identifies the text on the Display is to change.
  display_changed = TRUE;
  
  enable_interrupts();
  set_baud_one();
  P3OUT |= IOT_EN_CPU;
  P3OUT &= ~IOT_EN_CPU;
  
  //------------------------------------------------------------------------------
  // Beginning of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      
    
    
    if(count>COUNT_CHECK){
      if(startflg == RESET){               //turn on reset for iot module
        P3OUT |= IOT_EN_CPU;
        startflg = SETHI;
      }
      if(controldispflag == RESET){
        strcpy(display_line[DISPLINE1], "  Waiting ");
        strcpy(display_line[DISPLINE2], " for Input");
        display_changed = SETHI;
      }
      else{
        if(stopflagfinal == RESET){
          strcpy(display_line[DISPLINE2], tempip);
          strcpy(display_line[DISPLINE3], tempip2);
          display_changed = SETHI;
          if(flag200ms == SETHI){
            flag200ms = SETLOW;
            count200ms();
          }
        }
      }
      
      
      //line follow case statement
      
      if(autoflagmain == SETHI){            //code to initially find and turn on to line
        
        if(LEFT_DETECT > DETECT_LIM || RIGHT_DETECT > DETECT_LIM){
          strcpy(display_line[DISPLINE1], "BL Start  ");                        //black line found
          display_changed = SETHI;
          update_display = SETHI;
          Display_Process();
          for(timer50ms=RESET;timer50ms<pause;timer50ms = timer50ms){
            if(flag200ms == SETHI){
              flag200ms = SETLOW;
              count200ms();
            }
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_LO;
          }
          strcpy(display_line[DISPLINE1], "BL Turn   ");
          display_changed = SETHI;
          update_display = SETHI;
          Display_Process();
         
          while(LEFT_DETECT<DETECT_LIM){
            RIGHT_REVERSE_SPEED = Spin_Speed;
            LEFT_FORWARD_SPEED = Spin_Speed;
          }
          
          for(timer50ms=RESET;timer50ms<pause;timer50ms = timer50ms){
            if(flag200ms == SETHI){
              flag200ms = SETLOW;
              count200ms();
            }
            RIGHT_REVERSE_SPEED = MOTOR_LO;
            LEFT_REVERSE_SPEED = MOTOR_LO;
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_LO;
          }
          
          
          
          strcpy(display_line[DISPLINE1], "BL Travel ");
          display_changed = SETHI;
          update_display = SETHI;
          Display_Process();
          
          linefollowflag = SETHI;
          autoflagmain = RESET;
          circletimer = RESET;
        }
      }
      if(linefollowflag == SETHI && autoflagmain == RESET){               //three possible cases for traversing black line
        
        if(circletimer == circtime){
          strcpy(display_line[DISPLINE1], "BL Circle ");
          display_changed = SETHI;
          update_display = SETHI;
          Display_Process();
          for(timer50ms = RESET;timer50ms < pause;timer50ms=timer50ms){
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_LO;
            if(flag200ms == SETHI){
              flag200ms = SETLOW;
              count200ms();
            }
          }
        }
        
        if(LEFT_DETECT > DETECT_LIM && RIGHT_DETECT < DETECT_LIM){
          RIGHT_FORWARD_SPEED = MOTOR_LO;
          LEFT_FORWARD_SPEED = MOTOR_STANDARD;
        }
        
        if(LEFT_DETECT < DETECT_LIM && RIGHT_DETECT > DETECT_LIM){
          RIGHT_FORWARD_SPEED = MOTOR_STANDARD;
          LEFT_FORWARD_SPEED = MOTOR_LO;
        }
        
        if(LEFT_DETECT > DETECT_LIM && RIGHT_DETECT > DETECT_LIM){
          RIGHT_FORWARD_SPEED = MOTOR_STANDARD;
          LEFT_FORWARD_SPEED = MOTOR_STANDARD;
        }
      }
      
      
      
      //code for sending message to iot
          
      topnonvol = top;
      if(bottom != topnonvol){
        
        if(startflg == STATE1 && RxBUFF[bottom][G_Location] == 'G'){
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          UCA0IE |= UCTXIE;
          
        }
        
        if(RxBUFF[bottom][K_Location]=='K' && startflg == STATE2){
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT+SYSSTORE=0\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          UCA0IE |= UCTXIE;
          
        }
        
        if(RxBUFF[bottom][K_Location]=='K' && startflg == STATE3){
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT+CIPMUX=1\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          UCA0IE |= UCTXIE;
          
        }
        
        
        if(RxBUFF[bottom][K_Location]=='K' && startflg == STATE4){
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT+CIPSERVER=1,1080\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          testflag = SETHI;
          UCA0IE |= UCTXIE;
          
        }
        
        
        if(startflg == STATE5 && RxBUFF[bottom][K_Location] == 'K'){
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT+CIFSR\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          UCA0IE |= UCTXIE;
          
        }
        
        
        
        if(RxBUFF[bottom][Plus_Location]=='+' && RxBUFF[bottom][IP_Location] == 'P'){             //ip recieved
          for(int j= IP_Init; RxBUFF[bottom][j] != '"' && j<IP_Lim;j++){
            tempip[tempipcount] = RxBUFF[bottom][j]; 
            tempipcount++;
            tempipcount2++;
          }
          strcpy(display_line[DISPLINE1], tempip);
          
          tempipcount = RESET;
          for(int j = IP_Init+tempipcount2; RxBUFF[bottom][j] != '"';j++){         //print ip to display
            tempip2[tempipcount] = RxBUFF[bottom][j]; 
            tempipcount++;
          }
          strcpy(display_line[DISPLINE2], tempip2);
          display_changed = SETHI;
          
          iot_rx_read = RESET;
          strcpy(iot_transmit1, "AT+CWJAP?\r\n");
          Setup_transfer_size = sizeof(iot_transmit1);
          UCA0IE |= UCTXIE;
        }
        
        
        if(RxBUFF[bottom][Plus_Location]=='+' && RxBUFF[bottom][SSID_Location] == 'J'){             //ssid received
          tempipcount = RESET;
          for(int j= SSID_Init; RxBUFF[bottom][j] != '"' && j<SSID_Lim;j++){
            ssidprint[tempipcount] = RxBUFF[bottom][j]; 
            tempipcount++;
          }
          strcpy(display_line[DISPLINE1], ssidprint);
          display_changed = SETHI;
          mainstate = SETHI;
        }        
        
        if(RxBUFF[bottom][Key] == '^' && RxBUFF[bottom][Pass1] == '4' && RxBUFF[bottom][Pass2] == '3' && RxBUFF[bottom][Pass3] == '2' && RxBUFF[bottom][Pass4] == '1'){   //check for ^ and passcode
          tempipcount = SETLOW;
          tempipcount = PROCESS_SIZE;
          controldispflag = SETHI;
          for(int i = RESET; i<FOUR;i++){                              //convert string to int and char for movement function
            movetime[i] = RxBUFF[bottom][tempipcount];
            tempipcount++;   
          }
          
          movetimeint = atoi(movetime); 
          movetimeint = movetimeint/HUNDRED;
          display_changed = SETHI;
          
          switch(RxBUFF[bottom][Direction]){
          case 'F':                                       //go forwards         
            //strcpy(display_line[DISPLINE2], "  Forward ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            RIGHT_FORWARD_SPEED = MOTOR_FAST;
            LEFT_FORWARD_SPEED = MOTOR_FAST;
            
            break;
            
            
          case 'B':                                       //go backwards         
            //strcpy(display_line[DISPLINE2], "  Back    ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            for(timer50ms = SETLOW;timer50ms<Reverse_Time;timer50ms = timer50ms){
              RIGHT_REVERSE_SPEED = MOTOR_FAST;
              LEFT_REVERSE_SPEED = MOTOR_FAST;
            }
            RIGHT_REVERSE_SPEED = SETLOW;
            LEFT_REVERSE_SPEED = SETLOW;
            
            break;
          case 'X':                                       //go forwards small        
            //strcpy(display_line[DISPLINE2], "  Forward ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            for(timer50ms = RESET;timer50ms<Forward_Time;timer50ms = timer50ms){
              RIGHT_FORWARD_SPEED = MOTOR_FAST;
              LEFT_FORWARD_SPEED = MOTOR_FAST;
            }
            RIGHT_FORWARD_SPEED = SETLOW;
            LEFT_FORWARD_SPEED = SETLOW;
            
            break;
            
          case 'E':                               //exit from circle 
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            strcpy(display_line[DISPLINE2], "BL Exit   ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            linefollowflag = SETLOW;
            for(timer50ms = RESET;timer50ms<Forward_Time;timer50ms = timer50ms){
              RIGHT_FORWARD_SPEED = MOTOR_FAST;
              LEFT_FORWARD_SPEED = MOTOR_FAST;
              if(flag200ms == SETHI){
                flag200ms = SETLOW;
                count200ms();
              }
            }
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_LO;
            
            stopflagfinal = SETHI;
            strcpy(display_line[DISPLINE2], "BL Stop   ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            
            break;
            
          case 'L':                                               //left turn         
            //strcpy(display_line[DISPLINE2], "    Left  ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            //run_case(500,10000,10000,movetimeint);
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_FAST;
            
            break;
            
          case 'R':                                               //right turn                  
            //strcpy(display_line[DISPLINE2], "   Right  ");
            display_changed = 1;
            update_display = 1;
            Display_Process();
            //run_case(10000,500,10000,movetimeint);
            RIGHT_FORWARD_SPEED = MOTOR_FAST;
            LEFT_FORWARD_SPEED = MOTOR_LO;
            
            break;
            
          case 'A':                                               //start auto
            strcpy(display_line[DISPLINE1], "BL Start  ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            
            for(timer50ms = RESET;timer50ms<pause;timer50ms = timer50ms){        //pause for viewing
              if(flag200ms == SETHI){
                flag200ms = SETLOW;
                count200ms();
              }
              RIGHT_FORWARD_SPEED = MOTOR_LO;
              LEFT_FORWARD_SPEED = MOTOR_LO;
            }
            for(timer50ms = RESET;timer50ms<Forward_Time;timer50ms = timer50ms){         //forward movement
              if(flag200ms == SETHI){
                flag200ms = SETLOW;
                count200ms();
              }
              RIGHT_FORWARD_SPEED = MOTOR_STANDARD;
              LEFT_FORWARD_SPEED = MOTOR_STANDARD;
            }
            
            RIGHT_FORWARD_SPEED = MOTOR_FAST;                                  //arcspeed
            LEFT_FORWARD_SPEED = MOTOR_SLOW;
            autoflagmain = SETHI;
            break;
            
          case 'C':
            strcpy(display_line[DISPLINE1], "         ");         //to clear line 1 of display
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            
            break;
            
          case 'S':                                               //stop bot
            //strcpy(display_line[DISPLINE2], "  STOP   ");
            display_changed = SETHI;
            update_display = SETHI;
            Display_Process();
            autoflagmain = RESET;
            linefollowflag = RESET;
            RIGHT_FORWARD_SPEED = MOTOR_LO;
            LEFT_FORWARD_SPEED = MOTOR_LO;
            
            break;
            
          case 'P':                //display pad number
            switch(oddeven){
            case STATE1:
              strcpy(display_line[DISPLINE1], "Arrived 1");
              display_changed = SETHI;
              break;
            case STATE2:
              strcpy(display_line[DISPLINE1], "Arrived 2");
              display_changed = SETHI;
              break;
            case STATE3:
              strcpy(display_line[DISPLINE1], "Arrived 3");
              display_changed = SETHI;
              break;
            case STATE4:
              strcpy(display_line[DISPLINE1], "Arrived 4");
              display_changed = SETHI;
              break;
            case STATE5:
              strcpy(display_line[DISPLINE1], "Arrived 5");
              display_changed = SETHI;
              break;
            case STATE6:
              strcpy(display_line[DISPLINE1], "Arrived 6");
              display_changed = SETHI;
              break;
            case STATE7:
              strcpy(display_line[DISPLINE1], "Arrived 7");
              display_changed = SETHI;
              break;
            default:
              break;
            }
            
            oddeven++;
            
            update_display = SETHI;
            Display_Process();
            
            break;
          default: break;
          }
          count200[BEGINNING] = RxBUFF[bottom][Direction];
          Display_Process();
          
          
        }
       
        for(int i = RESET;i<RING_SIZE;i++){
          RxBUFF[bottom][i] = RESET;
          
        }
        
        
        
      }
      
      
      
      
      bottom++; //increment slow point
      if(bottom>prolim){
        bottom = RESET;
      }
    }
    
  }
}


//------------------------------------------------------------------------------
//}



void Display_Process(void){
  if(update_display){
    update_display = SETLOW;
    if(display_changed){
      display_changed = SETLOW;
      Display_Update(SETLOW,SETLOW,SETLOW,SETLOW);
    }
  }
}

