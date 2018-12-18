// Authors: Dalton Altstaetter & Ken Lee
// February 3, 2015
// EE445M Spring 2015

extern long StartCritical(void);     // previous I bit, disable interrupts
extern void EndCritical(long sr);    // restore I bit to previous value

// these are stored in a buffer to easily start tasks by enabling the timer
#define TIMER0_CTL_PTR_R            (volatile uint32_t *)0x4003000C
#define TIMER1_CTL_PTR_R            (volatile uint32_t *)0x4003100C
#define TIMER2_CTL_PTR_R            (volatile uint32_t *)0x4003200C
#define TIMER3_CTL_PTR_R            (volatile uint32_t *)0x4003300C
#define TIMER4_CTL_PTR_R            (volatile uint32_t *)0x4003400C
#define TIMER5_CTL_PTR_R            (volatile uint32_t *)0x4003500C
	
#define CLOCKSPEED_80MHZ			80000000 // 80 MHz





//
int OS_TimerInit(void(*task)(void), int timer, unsigned long period, unsigned long priority);
int OS_AddPeriodicThread(void(*task)(void), int timer, unsigned long period, unsigned long priority);

// Resets the 32-bit counter to zero
void OS_ClearPeriodicTime(int timer);

// Returns the number of bus cycles in a full period
unsigned long OS_ReadTimerPeriod(int timer);
unsigned long OS_ReadTimerValue(int timer);

void OS_LaunchThread(void(*task)(void), int timer);
void OS_StopThread(void(*taskPtr)(void), int timer);
void GPIO_PortF_Init(void);
void PF1_Toggle(void);





