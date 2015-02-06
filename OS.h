// Authors: Dalton Altstaetter & Ken Lee
// February 3, 2015
// EE445M Spring 2015

extern long StartCritical(void);     // previous I bit, disable interrupts
extern void EndCritical(long sr);    // restore I bit to previous value
//
int OS_AddPeriodicThread(void(*task)(void), unsigned long period, unsigned long priority, int timer);

// Resets the 32-bit counter to zero
void OS_ClearPeriodicTime(int timer);

// Returns the number of bus cycles in a full period
unsigned long OS_ReadPeriodicTime(int timer);






