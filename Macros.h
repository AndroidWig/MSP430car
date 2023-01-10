//------------------------------------------------------------------------------
//
//  Description: This file contains macros for easier code reading
//
//
//  Jason Robinson
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include "ports.h"

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
#define RED_LED                (0x01) // 1.0 RED LED 0
#define GRN_LED                (0x40) // 6.6 GREEN LED
#define DISPARR                 (4)
#define DISPLINEARR             (11)
#define SETLOW                  (0)
#define SETHI                   (1)
#define DISPLINE1               (0)
#define DISPLINE2               (1)
#define DISPLINE3               (2)
#define DISPLINE4               (3)
#define CASE1                   (250)
#define CASE2                   (200)
#define CASE3                   (150)
#define CASE4                   (100)
#define CASE5                   (50)
#define MAX                     (10)
#define RESET                   (0)
#define SECOND                   (2)
#define THIRD                   (3)
#define FOUR                      (4)
#define FIVE (5)

#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define TRIANGLE ('T')
#define FIG8 ('F')
#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define END ('E')
#define WHEEL_COUNT_TIME (10)
#define RIGHT_COUNT_TIME (7)
#define LEFT_COUNT_TIME (8)
#define TRAVEL_DISTANCE (2)
#define WAITING2START (50)

#define NOT_OKAY (0)
#define DEBOUNCE_RESTART (0)
#define OKAY (1)
#define PRESSED (0)
#define RELEASED (1)

//project 05
#define TB0CCR0_INTERVAL (62500) //half a second initial/first/second/mhz
#define TB0CCR1_INTERVAL (6250) //50 ms
#define adcinterval (1250)
#define TB0CCR2_INTERVAL (25000)  //display update timer
#define Second_20 (20)

//hw 06
// Main While loop switch cases
#define Time_Sequence_Rate (50) // 50 millisecods
#define S1250 (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000 (1000/Time_Sequence_Rate) // 1 second
#define S750 (750/Time_Sequence_Rate) // 0.75 seconds
#define S500 (500/Time_Sequence_Rate) // 0.50 seconds
#define S250 (250/Time_Sequence_Rate) // 0.25 seconds

#define initflag (1)


//project 06
#define WHEEL_PERIOD (20000)
#define WHEEL_OFF (0)
#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define RIGHT_REVERSE_SPEED (TB3CCR2)
#define LEFT_FORWARD_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define DETECT_LIM (800)
#define TURN_SPEED (3000)
#define MOTOR_HI (6500)
#define MOTOR_LO (0)
#define COUNT_CHECK (2)
#define FOUR (4)
#define NINE (9)
#define NINENINE (99)
#define NINENINENINE (999)
#define THOUSAND (1000)
#define HUNDRED (100)
#define TEN (10)
#define ASCII (0x30)

//project 08
#define BEGINNING (0)
#define RING_SIZE (64)          //changed for project 09
#define LCD_INDEX (10)
#define UCBRx_BAUD_1 (4)
#define UCBRx_BAUD_2 (17) //may be 1
#define BITCLK_BAUD_1 (0x5551) //may be 5551
#define BITCLK_BAUD_2 (0x4A00)// may be 4A00
#define PROCESS_SIZE (16) //////////////////////////////////////// must be same as ring size
#define VECTOR_0 (0)
#define SERIAL_FLAGS (0x08)
#define TXIFG (4)
#define RXIFG (2)
#define outsize (11)
#define setup (0)
#define movement (1)
#define prolim (8)
#define TWO (2)

//project 10
#define pause (15)
#define circtime (25)
#define MOTOR_STANDARD (8000)
#define STATE1 (1)
#define STATE2 (2)
#define STATE3 (3)
#define STATE4 (4)
#define STATE5 (5)
#define STATE6 (6)
#define STATE7 (7)
#define STATE14 (14)
#define K_Location (1)
#define Plus_Location (0)
#define IP_Location (11)
#define IP_Init (14)
#define IP_Lim (24)
#define SSID_Location (3)
#define SSID_Init (8)
#define SSID_Lim (19)
#define Key (1)
#define Pass1 (11)
#define Pass2 (12)
#define Pass3 (13)
#define Pass4 (14)
#define Direction (15)
#define Reverse_Time (3)
#define MOTOR_FAST (11000)
#define Forward_Time (4)
#define MOTOR_SLOW (6000)
#define G_Location (5)
#define Spin_Speed (4750)
#define ONES (7)
#define TENS (6)
#define HUNDREDS (5)
#define DECIMAL (9)
#define INCREMENT (1)
