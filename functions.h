//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jason Robinson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
//void Init_Port3(char smclk);
void Init_Port3(void); //Remove This when its relevant.
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

void run_case(unsigned int LS, unsigned int RS, unsigned int Tot, unsigned int movementtime);
void Run_Straight(void);

//display
void dispcirc(void);
void disptri(void);
void dispfig8(void);
void sw1press(void);
void sw2press(void);

//project 05
void motorstop(void);
void motorfwd(void);
void spinCW(void);
void spinCCW(void);
void motorrev(void);
void dispfwd(void);
void dispstop(void);
void dispcw(void);
void dispccw(void);
void disprev(void);
void Forward_On(void);

//project 07
void Init_ADC(void);
void ADC_interrupts(void);
void Init_DAC(void);
void Init_REF(void);
void HEXtoBCD(int);
void adc_line(char line, char location);
void Wheels_Process(void);
void DISP_BLACK(void);
void circfin(void);
void dispintercept(void);
//void dispwait(void);
void dispturn(void);
void dispcircling(void);
void dispstopped(void);
void disprefind(void);
void count200ms(void);

//project 08
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);
void set_baud_one(void);
void set_baud_two(void);
void dispbaud(void);
void disprate1(void);
void disprate2(void);
void clear2lines(void);
void initserial(void);
void clear_ring_buffs(void);
void dispwait(void);
void disptransmit(void);
void dispreceived(void);
void clearline1(void);
void clearline4(void);

//project 09
void IOT_Process(void);
void motormove(char, int);

