
// Authors: Dalton Altstaetter & Ken Lee
// February 3, 2015
// EE445M Spring 2015

#include "OS.h"
#include "inc/tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>
#include "TIMER.h"
#include "PLL.h"


#define TESTING


//void(*HandlerTaskArray[12])(void); // Holds the function pointers to the threads that will be launched



//int OS_TimerInit(void(*task)(void), int timer, unsigned long period, unsigned long priority);


// used to store the addresses of the TIMERX_CTRL_R to do the operatin *(timerCtrlBuf[x]) |= TIMER_CTL_TXEN_
//static volatile unsigned int* timerCtrlBuf[12] = {TIMER0_CTL_PTR_R, TIMER0_CTL_PTR_R, TIMER1_CTL_PTR_R, TIMER1_CTL_PTR_R,
//																									TIMER2_CTL_PTR_R, TIMER2_CTL_PTR_R, TIMER3_CTL_PTR_R, TIMER3_CTL_PTR_R,
//																									TIMER4_CTL_PTR_R, TIMER4_CTL_PTR_R, TIMER5_CTL_PTR_R, TIMER5_CTL_PTR_R};
//static int usedTimers[12];
//static int timerCount = -1;


// initializes a new thread with given period and priority
int OS_AddPeriodicThread(void(*task)(void), int timer, unsigned long period, unsigned long priority)
{// period and priority are used when initializing the timer interrupts
	int status;
	int sr;
	sr = StartCritical();
	// initialize a timer specific to this thread
	// each timer should be unique to a thread so that it can interrupt when
	// it counts to 0 and sets the flag, this requires counting timers
	
	status = 0;
	status = TIMER_TimerInit(task,timer, period, priority);
	if(status == -1)
	{
		//printf("Error Initializing timer number(0-11): %d\n", timer);
	}
	
	EndCritical(sr);
	return 0;
}

/*
// Resets the 32-bit counter to zero
void OS_ClearPeriodicTime(int timer)
{
	switch(timer)
	{
		case 0: // TIMERA0
			TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA0
			TIMER0_TAV_R = 0; // set Timer to 0
			TIMER0_CTL_R |= TIMER_CTL_TAEN; // enable TimerA0
			break;
		
		case 1: // TIMERB0
			TIMER0_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB0
			TIMER0_TBV_R = 0; // set Timer to 0
			TIMER0_CTL_R |= TIMER_CTL_TBEN; // enable TimerB0
			break;
		
		case 2: // TIMERA1
			TIMER1_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA1
			TIMER1_TAV_R = 0; // set Timer to 0
			TIMER1_CTL_R |= TIMER_CTL_TAEN; // enable TimerA1
			break;
		
		case 3:	// TIMERB1
			TIMER1_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB1
			TIMER1_TBV_R = 0; // set Timer to 0
			TIMER1_CTL_R |= TIMER_CTL_TBEN; // enable TimerB1
			break;
		
		case 4:	// TIMERA2
			TIMER2_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA2
			TIMER2_TAV_R = 0; // set Timer to 0 = 0; // set Timer to 0
			TIMER2_CTL_R |= TIMER_CTL_TAEN; // enable TimerA2
			break;
		
		case 5:	// TIMERB2
			TIMER2_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB2
			TIMER2_TBV_R = 0; // set Timer to 0 = 0; // set Timer to 0
			TIMER2_CTL_R |= TIMER_CTL_TBEN; // enable TimerB2
			break;
		
		case 6: // TIMERA3
			TIMER3_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA3
			TIMER3_TAV_R = 0; // set Timer to 0
			TIMER3_CTL_R |= TIMER_CTL_TAEN; // enable TimerA3
			break;
		
		case 7:	// TIMERB3
			TIMER3_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB3
			TIMER3_TBV_R = 0; // set Timer to 0
			TIMER3_CTL_R |= TIMER_CTL_TBEN; // enable TimerB3
			break;
		
		case 8: // TIMERA4
			TIMER4_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA4
			TIMER4_TAV_R = 0; // set Timer to 0
			TIMER4_CTL_R |= TIMER_CTL_TAEN; // enable TimerA4
			break;
		
		case 9: // TIMERB4
			TIMER4_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB4
			TIMER4_TBV_R = 0; // set Timer to 0
			TIMER4_CTL_R |= TIMER_CTL_TBEN; // enable TimerB4
			break;
		
		case 10: // TIMERA5
			TIMER5_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA5
			TIMER5_TAV_R = 0; // set Timer to 0
			TIMER5_CTL_R |= TIMER_CTL_TAEN; // enable TimerA5
			break;
		
		case 11: // TIMERB5
			TIMER5_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB5
			TIMER5_TBV_R = 0; // set Timer to 0
			TIMER5_CTL_R |= TIMER_CTL_TBEN; // enable TimerB5
			break;
		
		default:
			break;
	}
}
*/

// Returns the number of bus cycles in a full period
/*
unsigned long OS_ReadTimerPeriod(int timer)
{
	unsigned long busCyclePerPeriod = 0;
	switch(timer)
	{
		case 0:
			busCyclePerPeriod = TIMER0_TAILR_R;
			break;
		
		case 1:
			busCyclePerPeriod = TIMER0_TBILR_R;
			break;
		
		case 2:
			busCyclePerPeriod = TIMER1_TAILR_R;
			break;
		
		case 3:
			busCyclePerPeriod = TIMER1_TBILR_R;
			break;
		
		case 4:
			busCyclePerPeriod = TIMER2_TAILR_R;
			break;
		
		case 5:
			busCyclePerPeriod = TIMER2_TBILR_R;
			break;
		
		case 6:
			busCyclePerPeriod = TIMER3_TAILR_R;
			break;
		
		case 7:
			busCyclePerPeriod = TIMER3_TBILR_R;
			break;
		
		case 8:
			busCyclePerPeriod = TIMER4_TAILR_R;
			break;
		
		case 9:
			busCyclePerPeriod = TIMER4_TBILR_R;
			break;
		
		case 10:
			busCyclePerPeriod = TIMER5_TAILR_R;
			break;
		
		case 11:
			busCyclePerPeriod = TIMER5_TBILR_R;
			break;
		
		default:
			break;
	}
	return busCyclePerPeriod;
}
*/

/*unsigned long OS_ReadTimerValue(int timer)
{
	unsigned long count = 0;
	switch(timer)
	{
		case 0: // TimerA0
			count =  TIMER0_TAR_R; // Read value, x, stored in Timer0, 0 < x < TIMER0_TAILR
			break;
		
		case 1: // TimerB0
			count = TIMER0_TBR_R; // Read value, x, stored in Timer0, 0 < x < TIMER0_TBILR
			break;
			
		case 2: // TimerA1
			count = TIMER1_TAR_R; // Read value, x, stored in Timer1, 0 < x < TIMER1_TAILR
			break;
		
		case 3: // TimerB1
			count = TIMER1_TBR_R; // Read value, x, stored in Timer1, 0 < x < TIMER1_TBILR
			break;
		
		case 4: // TimerA2
			count = TIMER2_TAR_R; // Read value, x, stored in Timer2, 0 < x < TIMER2_TAILR
			break;
		
		case 5: // TimerB2
			count = TIMER2_TBR_R; // Read value, x, stored in Timer2, 0 < x < TIMER2_TBILR
			break;
		
		case 6: // TimerA3
			count = TIMER3_TAR_R; // Read value, x, stored in Timer3, 0 < x < TIMER3_TAILR
			break;
		
		case 7: // TimerB3
			count = TIMER3_TBR_R; // Read value, x, stored in Timer3, 0 < x < TIMER3_TBILR
			break;
		
		case 8: // TimerA4
			count = TIMER4_TAR_R; // Read value, x, stored in Timer4, 0 < x < TIMER4_TAILR
			break;
		
		case 9: // TimerB4
			count = TIMER4_TBR_R; // Read value, x, stored in Timer4, 0 < x < TIMER4_TBILR
			break;
		
		case 10: // TimerA5
			count = TIMER5_TAR_R; // Read value, x, stored in Timer5, 0 < x < TIMER5_TAILR
			break;
		
		case 11: // timerB5
			count = TIMER5_TBR_R; // Read value, x, stored in Timer5, 0 < x < TIMER5_TBILR
			break;
		
		default:
			break;
	}
	return count;
}
*/

// launches all programs
//void OS_LaunchAll(void(**taskPtrPtr)(void))
//{
////	int i;
////	int timerN;
////	unsigned int TAEN_TBEN;
////	for(i = 0; i <= timerCount; i++)
////	{
////		timerN = usedTimers[i]; // its the timerID 0 to 11
////		TAEN_TBEN = ((timerN%2) ? TIMER_CTL_TBEN:TIMER_CTL_TAEN); // if timerN even => TAEN, timerN odd => TBEN
////		*(timerCtrlBuf[timerN]) |= TAEN_TBEN;
////	}
//	
//	// this assumes that the timers initialized in the same sequence as the tasks
//	// i.e. usedTimer[i] was initialized for the functionPtr *(taskPtrPtr[i]) 
//	int i;
//	for(i = 0; i <= timerCount; i++)
//	{
//		OS_LaunchThread(taskPtrPtr[i],usedTimers[i]);
//	}
//}

/*
// enables interrupts in the NVIC vector table
void OS_NVIC_EnableTimerInt(int timer)
{
	switch(timer)
	{
		case 0: // Timer0A
			NVIC_EN0_R = NVIC_EN0_INT19;
			break;
		
		case 1: // Timer0B
			NVIC_EN0_R = NVIC_EN0_INT20;
			break;
		
		case 2: // Timer1A
			NVIC_EN0_R = NVIC_EN0_INT21;
			break;
			
		case 3: // Timer1B
			NVIC_EN0_R = NVIC_EN0_INT22;
			break;
			
		case 4: // Timer2A
			NVIC_EN0_R = NVIC_EN0_INT23;
			break;
		
		case 5: // Timer2B
			NVIC_EN0_R = NVIC_EN0_INT24;
			break;
		
		case 6: // Timer3A
			NVIC_EN1_R = NVIC_EN1_INT35;
			break;
			
		case 7: // Timer3B
			NVIC_EN1_R = NVIC_EN1_INT36;
			break;
		
		case 8: // Timer4A
			NVIC_EN2_R = NVIC_EN2_INT70;
			break;
			
		case 9: // Timer4B
			NVIC_EN2_R = NVIC_EN2_INT71;
			break;
			
		case 10: // Timer5A
			NVIC_EN2_R = NVIC_EN2_INT92;
			break;
		case 11: // Timer5B
			NVIC_EN2_R = NVIC_EN2_INT93;
			break;
	}
}
*/



/*
void OS_NVIC_DisableTimerInt(int timer)
{
	switch(timer)
	{
		case 0: // Timer0A
			NVIC_DIS0_R = NVIC_DIS0_INT19;
			break;
		
		case 1: // Timer0B
			NVIC_DIS0_R = NVIC_DIS0_INT20;
			break;
		
		case 2: // Timer1A
			NVIC_DIS0_R = NVIC_DIS0_INT21;
			break;
			
		case 3: // Timer1B
			NVIC_DIS0_R = NVIC_DIS0_INT22;
			break;
			
		case 4: // Timer2A
			NVIC_DIS0_R = NVIC_DIS0_INT23;
			break;
		
		case 5: // Timer2B
			NVIC_DIS0_R = NVIC_DIS0_INT24;
			break;
		
		case 6: // Timer3A
			NVIC_DIS1_R = NVIC_DIS1_INT35;
			break;
			
		case 7: // Timer3B
			NVIC_DIS1_R = NVIC_DIS1_INT36;
			break;
		
		case 8: // Timer4A
			NVIC_DIS2_R = NVIC_DIS2_INT70;
			break;
			
		case 9: // Timer4B
			NVIC_DIS2_R = NVIC_DIS2_INT71;
			break;
			
		case 10: // Timer5A
			NVIC_DIS2_R = NVIC_DIS2_INT92;
			break;
		case 11: // Timer5B
			NVIC_DIS2_R = NVIC_DIS2_INT93;
			break;
	}
}
*/

void OS_LaunchThread(void(*taskPtr)(void), int timer)
{
	int timerN;
	unsigned int TAEN_TBEN;

	timerN = timer; // its the timerID (0 to 11)
	TIMER_NVIC_EnableTimerInt(timer);
	TAEN_TBEN = ((timerN%2) ? TIMER_CTL_TBEN : TIMER_CTL_TAEN); // if timerN even => TAEN, timerN odd => TBEN
	*(timerCtrlBuf[timerN]) |= TAEN_TBEN; // start timer for this thread, X in {0,1,2,3,4,5}, x in {A,B}
	// ^^^ is *(TIMERX_CTRL_PTR_R) |= TIMER_CTL_TxEN and/or TIMERX_CTL_R |= TIMER_CTL_TxEN
	//(*taskPtr)(); // begin task for this thread Do this in the ISR
}

void OS_StopThread(void(*taskPtr)(void), int timer)
{
	int timerN;
	unsigned int TAEN_TBEN;

	timerN = timer; // its the timerID (0 to 11)
	TIMER_NVIC_DisableTimerInt(timer);
	TAEN_TBEN = ((timerN%2) ? TIMER_CTL_TBEN : TIMER_CTL_TAEN); // if timerN even => TAEN, timerN odd => TBEN
	*(timerCtrlBuf[timerN]) &= ~TAEN_TBEN; // start timer for this thread, X in {0,1,2,3,4,5}, x in {A,B}
	// ^^^ is *(TIMERX_CTRL_PTR_R) |= TIMER_CTL_TxEN and/or TIMERX_CTL_R |= TIMER_CTL_TxEN
	//(*taskPtr)(); // begin task for this thread Do this in the ISR
}

// this configures the timers for 32-bit mode, periodic mode
//
//static int OS_TimerInit(void(*task)(void), int timer, unsigned long desiredFrequency, unsigned long priority)
//{
//	int delay;
//	unsigned long cyclesPerPeriod;
//	
//	// will fail if frequency is a decimal number close to 0 relative to the bus speed
//	cyclesPerPeriod = CLOCKSPEED_80MHZ/desiredFrequency; 
//	
//	switch(timer)
//	{
//		case 0:		//TimerA0
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;   // activate timer0
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA0
//			TIMER0_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER0_TAILR_R = cyclesPerPeriod-1;
//			TIMER0_TAPR_R = 0; // set prescale = 0
//			TIMER0_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER0_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI4_R = (NVIC_PRI4_R & ~NVIC_PRI4_INT19_M)|(priority << NVIC_PRI4_INT19_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER0_CTL_R |= TIMER_CTL_TAEN; // enable TimerA0, do this in OS_Launch(.)
//			HandlerTaskArray[0] = task; // fill function pointer array w/address of task
//			break;
//		
//		case 1:  	//TimerB0
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;   // activate timer0
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//		  TIMER0_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB0
//			TIMER0_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER0_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER0_TBILR_R = cyclesPerPeriod-1;
//			TIMER0_TBPR_R = 0; // set prescale = 0
//			TIMER0_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER0_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI5_R = (NVIC_PRI5_R & ~NVIC_PRI5_INT20_M)|(priority << NVIC_PRI5_INT20_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER0_CTL_R |= TIMER_CTL_TBEN; // enable TimerB0, do this in OS_Launch(.)
//			HandlerTaskArray[1] = task; // fill function pointer array w/address of task
//			break;
//		
//		case 2:		//TimerA1
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;   // activate timer1
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER1_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA1
//			TIMER1_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER1_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER1_TAILR_R = cyclesPerPeriod-1;
//			TIMER1_TAPR_R = 0; // set prescale = 0
//			TIMER1_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER1_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI5_R = (NVIC_PRI5_R & ~NVIC_PRI5_INT21_M)|(priority << NVIC_PRI5_INT21_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER1_CTL_R |= TIMER_CTL_TAEN; // enable TimerA1, do this in OS_Launch(.)
//			HandlerTaskArray[2] = task; // fill function pointer array w/address of task
//			break;
//		
//		case 3:		//TimerB1
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;   // activate timer1
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER1_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB1
//			TIMER1_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER1_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER1_TBILR_R = cyclesPerPeriod-1;
//			TIMER1_TBPR_R = 0; // set prescale = 0
//			TIMER1_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER1_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI5_R = (NVIC_PRI5_R & ~NVIC_PRI5_INT22_M)|(priority << NVIC_PRI5_INT22_S);
//			//TIMER1_CTL_R |= TIMER_CTL_TBEN; // enable TimerB1, do this in OS_Launch(.)
//			HandlerTaskArray[3] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 4:		//TimerA2
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R2;   // activate timer2
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER2_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA2
//			TIMER2_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER2_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER2_TAILR_R = cyclesPerPeriod-1;
//			TIMER2_TAPR_R = 0; // set prescale = 0
//			TIMER2_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER2_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI5_R = (NVIC_PRI5_R & ~NVIC_PRI5_INT23_M)|(priority << NVIC_PRI5_INT23_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER2_CTL_R |= TIMER_CTL_TAEN; // enable TimerA2, do this in OS_Launch(.)
//			HandlerTaskArray[4] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 5:		//TimerB2
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R2;   // activate timer2
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER2_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB2
//			TIMER2_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER2_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER2_TBILR_R = cyclesPerPeriod-1;
//			TIMER2_TBPR_R = 0; // set prescale = 0
//			TIMER2_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER2_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI6_R = (NVIC_PRI6_R & ~NVIC_PRI6_INT24_M)|(priority << NVIC_PRI6_INT24_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER2_CTL_R |= TIMER_CTL_TBEN; // enable TimerB2, do this in OS_Launch(.)
//			HandlerTaskArray[5] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 6:		//TimerA3
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;   // activate timer3
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER3_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA3
//			TIMER3_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER3_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER3_TAILR_R = cyclesPerPeriod-1;
//			TIMER3_TAPR_R = 0; // set prescale = 0
//			TIMER3_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER3_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI8_R = (NVIC_PRI8_R & ~NVIC_PRI8_INT35_M)|(priority << NVIC_PRI8_INT35_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER3_CTL_R |= TIMER_CTL_TAEN; // enable TimerA3, do this in OS_Launch(.)
//			HandlerTaskArray[6] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 7:		//TimerB3
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;   // activate timer3
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER3_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB3
//			TIMER3_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER3_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER3_TBILR_R = cyclesPerPeriod-1;
//			TIMER3_TBPR_R = 0; // set prescale = 0
//			TIMER3_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER3_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI9_R = (NVIC_PRI9_R & ~NVIC_PRI9_INT36_M)|(priority << NVIC_PRI9_INT36_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER3_CTL_R |= TIMER_CTL_TBEN; // enable TimerB3, do this in OS_Launch(.)
//			HandlerTaskArray[7] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 8:		//TimerA4
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R4;   // activate timer4
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER4_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA4
//			TIMER4_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER4_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER4_TAILR_R = cyclesPerPeriod-1;
//			TIMER4_TAPR_R = 0; // set prescale = 0
//			TIMER4_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER4_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI17_R = (NVIC_PRI17_R & ~NVIC_PRI17_INTC_M)|(priority << NVIC_PRI17_INTC_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER4_CTL_R |= TIMER_CTL_TAEN; // enable TimerA4, do this in OS_Launch(.)
//			HandlerTaskArray[8] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 9:		//TimerB4
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R4;   // activate timer4
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER4_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB4
//			TIMER4_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER4_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER4_TBILR_R = cyclesPerPeriod-1;
//			TIMER4_TBPR_R = 0; // set prescale = 0
//			TIMER4_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER4_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI17_R = (NVIC_PRI17_R & ~NVIC_PRI17_INTD_M)|(priority << NVIC_PRI17_INTD_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER4_CTL_R |= TIMER_CTL_TBEN; // enable TimerB4, do this in OS_Launch(.)
//			HandlerTaskArray[9] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 10:	//TimerA5
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R5;   // activate timer5
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER5_CTL_R &= ~TIMER_CTL_TAEN; // disable TimerA5
//			TIMER5_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
//			TIMER5_TAILR_R = cyclesPerPeriod-1;
//			TIMER5_TAPR_R = 0; // set prescale = 0
//			TIMER5_ICR_R = TIMER_ICR_TATOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER5_IMR_R |= TIMER_IMR_TATOIM; // arm the timeout interrupt
//			NVIC_PRI23_R = (NVIC_PRI23_R & ~NVIC_PRI23_INTA_M)|(priority << NVIC_PRI23_INTA_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER5_CTL_R |= TIMER_CTL_TAEN; // enable TimerA5, do this in OS_Launch(.)
//			HandlerTaskArray[10] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		case 11:	//TimerB5
//			SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R5;   // activate timer5
//			delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
//			TIMER5_CTL_R &= ~TIMER_CTL_TBEN; // disable TimerB5
//			TIMER5_CFG_R  = TIMER_CFG_32_BIT_TIMER; // configure for 32-bit mode
//			TIMER5_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
//			TIMER5_TBILR_R = cyclesPerPeriod-1;
//			TIMER5_TBPR_R = 0; // set prescale = 0
//			TIMER5_ICR_R = TIMER_ICR_TBTOCINT; // clear timeout flag, friendly since writing a 0 does nothing
//			TIMER5_IMR_R |= TIMER_IMR_TBTOIM; // arm the timeout interrupt
//			NVIC_PRI23_R = (NVIC_PRI23_R & ~NVIC_PRI23_INTB_M)|(priority << NVIC_PRI23_INTB_S); //clears PRI bits then shifts the mask into the appropriate place
//			//TIMER5_CTL_R |= TIMER_CTL_TBEN; // enable TimerB5, do this in OS_Launch(.)
//			HandlerTaskArray[11] = task; // fill function pointer array w/address of tasks
//			break;
//		
//		default:
//			return -1;
//	}
//	
//	timerCount++; // used for launching the correct number of threads that were successfully initialized
//	usedTimers[timerCount] = timer; // store the timerID of which timer to launch
//	return 0;
//}

#ifdef TESTING

static void GPIO_PortF_Init(void)
{
	unsigned long delay;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTF_DIR_R |= 0x0F; // PF0-3 output
	GPIO_PORTF_DEN_R |= 0x0F; // enable Digital IO on PF0-3
	GPIO_PORTF_AFSEL_R &= ~0x0F; // PF0-3 alt funct disable
	GPIO_PORTF_AMSEL_R &= ~0x0F; // disable analog functionality on PF0-3
	
	GPIO_PORTF_DATA_R = 0x00;
}

static void PF0_Toggle(void)
{	
	GPIO_PORTF_DATA_R ^= 0x01;
}

static void PF1_Toggle(void)
{
	GPIO_PORTF_DATA_R ^= 0x02;
}

static void PF2_Toggle(void)
{	
	GPIO_PORTF_DATA_R ^= 0x04;
}

static void PF3_Toggle(void)
{
	GPIO_PORTF_DATA_R ^= 0x08;
}


int main123ABC(void)
{
    int timer0;
    int priority0;
    int period0;
    
    int timer1;
    int priority1;
    int period1;
		
    int timer2;
    int priority2;
    int period2;
    
    int timer3;
    int priority3;
    int period3;
    
	
		PLL_Init();
		
    timer0 = 0;
    priority0 = 0;
    period0 = 10;
    
    timer1 = 2;
    priority1 = 0;
    period1 = 1000;
    
		timer2 = 4;
    priority2 = 0;
    period2 = 500000;
    
    timer3 = 6;
    priority3 = 0;
    period3 = 65;
		
		GPIO_PortF_Init();
		
    OS_AddPeriodicThread(&PF1_Toggle, timer0, period0, priority0);
 //   OS_AddPeriodicThread(&PF2_Toggle, timer1, period1, priority1);
 // 		OS_AddPeriodicThread(&PF2_Toggle, timer2, period2, priority2);
//    OS_AddPeriodicThread(&PF3_Toggle, timer3, period3, priority3);
    
    OS_LaunchThread(&PF1_Toggle, timer0);
//    OS_LaunchThread(&PF2_Toggle, timer1);
 //   OS_LaunchThread(&PF2_Toggle, timer2);
//    OS_LaunchThread(&PF3_Toggle, timer3);
		
    return 0;
}
#endif
/*
//void Timer0A_Handler(void)
//{
//	TIMER0_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[0]))(); // start Timer0A task
//	
//}

//void Timer0B_Handler(void)
//{
//	TIMER0_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[1]))(); // start Timer0B task
//	
//}

//void Timer1A_Handler(void)
//{
//	TIMER1_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[2]))(); // start Timer1A task
//	
//}

//void Timer1B_Handler(void)
//{
//	TIMER1_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[3]))(); // start Timer1B task
//	
//}

//void Timer2A_Handler(void)
//{
//	TIMER2_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[4]))(); // start Timer2A task
//	
//}

//void Timer2B_Handler(void)
//{
//	TIMER2_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[5]))(); // start Timer2B task
//	
//}

//void Timer3A_Handler(void)
//{
//	TIMER3_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[6]))(); // start Timer3A task
//	
//}

//void Timer3B_Handler(void)
//{
//	TIMER3_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[7]))(); // start Timer3B task
//	
//}

//void Timer4A_Handler(void)
//{
//	TIMER4_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[8]))(); // start Timer4A task
//	
//}

//void Timer4B_Handler(void)
//{
//	TIMER4_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[9]))(); // start Timer4B task
//	
//}

//void Timer5A_Handler(void)
//{
//	TIMER5_ICR_R = TIMER_ICR_TATOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[10]))(); // // start Timer5A task
//	
//}

//void Timer5B_Handler(void)
//{
//	TIMER5_ICR_R = TIMER_ICR_TBTOCINT; // acknowledge interrupt flag
//	(*(HandlerTaskArray[11]))(); // start Timer5B task
//	
//}
*/

