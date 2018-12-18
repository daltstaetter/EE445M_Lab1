// Authors: Dalton Altstaetter & Ken Lee
// February 3, 2015
// EE445M Spring 2015

extern long StartCritical(void);     // previous I bit, disable interrupts
extern void EndCritical(long sr);    // restore I bit to previous value





//
int OS_AddPeriodicThread(void(*task)(void), int timer, unsigned long period, unsigned long priority);

// Resets the 32-bit counter to zero
void OS_ClearPeriodicTime(int timer);

// Returns the number of bus cycles in a full period
//unsigned long OS_ReadTimerPeriod(int timer);
//unsigned long OS_ReadTimerValue(int timer);

void OS_LaunchThread(void(*task)(void), int timer);
void OS_StopThread(void(*taskPtr)(void), int timer);

//void GPIO_PortF_Init(void);
//void PF1_Toggle(void);





