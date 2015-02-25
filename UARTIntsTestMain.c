// UARTIntsTestMain.c
// Runs on LM4F120/TM4C123
// Tests the UART0 to implement bidirectional data transfer to and from a
// computer running HyperTerminal.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
   Program 5.11 Section 5.6, Program 3.10

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include <stdint.h>
#include "PLL.h"
#include "UART.h"
//#include "ST7735.h"
#include "ADC.h"
#include "OS.h"
#include "inc/tm4c123gh6pm.h"


//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}

void GPIO_PortF_Init(void)
{
	unsigned long delay;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTF_DIR_R |= 0x0F; // PF0-3 output
	GPIO_PORTF_DEN_R |= 0x0F; // enable Digital IO on PF0-3
	GPIO_PORTF_AFSEL_R &= ~0x0F; // PF0-3 alt funct disable
	GPIO_PORTF_AMSEL_R &= ~0x0F; // disable analog functionality on PF0-3
	
	GPIO_PORTF_DATA_R = 0x02;
}

void PF1_Toggle(void)
{
		GPIO_PORTF_DATA_R ^= 0x02;
}

void PF2_Toggle(void)
{
		GPIO_PORTF_DATA_R ^= 0x04;
}

int main(void)
{
    int timer0;
    int priority0;
    int period0;
		
		int timer1;
    int priority1;
    int period1;
	
    timer0 = 1;
    priority0 = 0;
    period0 = 10;
	
    timer1 = 2;
    priority1 = 0;
    period1 = 20;
		
	  GPIO_PortF_Init();
//	  OS_AddPeriodicThread(&PF1_Toggle, timer0, period0, priority0);
    OS_AddPeriodicThread(&PF2_Toggle, timer0, period0, priority0);
 // 		OS_AddPeriodicThread(&PF2_Toggle, timer2, period2, priority2);
//    OS_AddPeriodicThread(&PF3_Toggle, timer3, period3, priority3);
    
//    OS_LaunchThread(&PF1_Toggle, timer0);
		OS_LaunchThread(&PF2_Toggle, timer0);
	
	while(1)
	{
	}
}

//debug code
int mainvfvf(void){
  char i;
  char string[20];  // global to assist in debugging
  uint32_t n;

  PLL_Init();               // set system clock to 50 MHz
  UART_Init();              // initialize UART
  OutCRLF();
  for(i='A'; i<='Z'; i=i+1){// print the uppercase alphabet
    UART_OutChar(i);
  }
  OutCRLF();
  UART_OutChar(' ');
  for(i='a'; i<='z'; i=i+1){// print the lowercase alphabet
    UART_OutChar(i);
  }
  OutCRLF();
  UART_OutChar('-');
  UART_OutChar('-');
  UART_OutChar('>');
  while(1){
    UART_OutString("InString: ");
    UART_InString(string,19);
    UART_OutString(" OutString="); UART_OutString(string); OutCRLF();

    UART_OutString("InUDec: ");  n=UART_InUDec();
    UART_OutString(" OutUDec="); UART_OutUDec(n); OutCRLF();

    UART_OutString("InUHex: ");  n=UART_InUHex();
    UART_OutString(" OutUHex="); UART_OutUHex(n); OutCRLF();

  }
}

int main2(void){
	PLL_Init();
	Output_Init();
	ST7735_Message(0,0,"Hello World",45);
	while(1){;}
}
