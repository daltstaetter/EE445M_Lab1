
// Authors: Dalton Altstaetter & Ken Lee
// February 3, 2015
// EE445M Spring 2015

#include "OS.h"
#include "inc/tm4c123gh6pm.h"


// initializes a new thread with given period and priority
int OS_AddPeriodicThread(void(*task)(void), unsigned long period, unsigned long priority, int timer)
{// period and priority are used when initializing the timer interrupts
	int sr = StartCritical();
	// initialize a timer specific to this thread
	// each timer should be unique to a thread so that it can interrupt when
	// it counts to 0 and sets the flag, this requires counting timers
	static int timerCount = 0;
	timerCount++;
	Timer_Init
	
	
	
	EndCritical(sr);
	return 0;
}

// Resets the 32-bit counter to zero
void OS_ClearPeriodicTime(int timer)
{
	// TAILTR = 0; // normally period -1
}

// Returns the number of bus cycles in a full period
unsigned long OS_ReadPeriodicTime(int timer)
{
	
	return 0;
}

// launches a main program
void OS_Launch(void(*task)(void))
{
	
}

static int OS_TimerInit(int timer)
{
	switch(timer)
	{
		case 0:		//TimerA0
			 
			break;
		
		case 1:  	//TimerB0
			
			break;
		
		case 2:		//TimerA1
			
			break;
		
		case 3:		//TimerB1
			
			break;
		
		case 4:		//TimerA2
			
			break;
		
		case 5:		//TimerB2
			
			break;
		
		case 6:		//TimerA3
			
			break;
		
		case 7:		//TimerB3
			
			break;
		
		case 8:		//TimerA4
			
			break;
		
		case 9:		//TimerB4
			
			break;
		
		case 10:	//TimerA5
			
			break;
		
		case 11:	//TimerB5
			
			break;
		
		default:
			return -1;
	}
}


