// ENGR-2350 Advanced Clocks
// Name: Kaylin Rackley
// RIN: 661810734

#include "engr2350_msp432.h"


// Add function prototypes here, as needed.
void Timer_Init();
void GPIO_Init();
void GPIO_INIT();
void UpdateTime();
void Timer_ISR();
void Port1_ISR();

// Add global variables here, as needed.
Timer_A_UpModeConfig clock;
uint8_t time[4];
uint8_t flag = 0;
uint8_t active_pins = 0;


int main(void) /* Main Function */
    {
    // Add local variables here, as needed.
    /*
    Timer_A_stopTimer(TIMER_A1_BASE); //timer pause
    Timer_A_getCounterValue(TIMER_A1_BASE); //shows time
    Timer_A_registerInterrupt( uint32_t timer , uint8_t interruptSelect , <function_name> );
    */

    SysInit();
    GPIO_Init();
    Timer_Init();

    while(1){
    }
}

// Add function declarations here as needed
void Timer_Init(){
        clock.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; //24 million ms
        clock.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64; // 24M/64 = 375000 ms
        clock.timerPeriod = 37500; // 375000/37500 = 100ms
        clock.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
        Timer_A_configureUpMode(TIMER_A1_BASE, &clock); //initialization
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE); //timer start
        Timer_A_registerInterrupt(TIMER_A1_BASE, TIMER_A_CCRX_AND_OVERFLOW_INTERRUPT, Timer_ISR);

}
void GPIO_Init(){
    GPIO_setAsOutputPin(5, GPIO_PIN7);
    GPIO_setAsInputPin(1, GPIO_PIN1);
    GPIO_setAsInputPin(1, GPIO_PIN4);
    GPIO_registerInterrupt(1, Port1_ISR);
    GPIO_interruptEdgeSelect(1, GPIO_PIN1 | GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(1, GPIO_PIN1 | GPIO_PIN4);



}
void UpdateTime(){
    time[0]++;  // Increment tenths of seconds
    if(time[0] == 10){  // If a whole second has passed...
        time[0] = 0;    // Reset tenths of seconds
        time[1]++;      // And increment seconds
        if(time[1] == 60){ // If a minute has passed...
            time[1] = 0;   // Reset seconds
            time[2]++;     // Increment minutes
            if(time[2] == 60){  // and so on...
                time[2] = 0;
                time[3]++;
                if(time[3] == 24){
                    time[3] = 0;
                }
            }
        }
    }
    printf("%2u:%02u:%02u.%u\r",time[3],time[2],time[1],time[0]);
}
void Timer_ISR(){
    Timer_A_clearInterruptFlag(TIMER_A1_BASE); // resets interrupt
    GPIO_toggleOutputOnPin(5, GPIO_PIN7); //toggles 5.7 when overflow is detected
    UpdateTime();
}
void Port1_ISR(){
    // First, we'll debouce the press to avoid multiple triggers for one press:
    __delay_cycles(240e3); // 10 ms delay (24 MHz clock)
     // Next: get the list of pins that may have triggered the interrupt
     active_pins = GPIO_getEnabledInterruptStatus(1);
     if(active_pins & GPIO_PIN1){
         GPIO_clearInterruptFlag(1,GPIO_PIN1);
         if(!GPIO_getInputPinValue(1,GPIO_PIN1)){
             time[1]++;      // And increment seconds
            if(time[1] == 60){ // If a minute has passed...
                time[1] = 0;   // Reset seconds
                time[2]++;     // Increment minutes
                if(time[2] == 60){  // and so on...
                   time[2] = 0;
                   time[3]++;
                   if(time[3] == 24){
                        time[3] = 0;
                   }
                }
            }
         }
     }
     active_pins = GPIO_getEnabledInterruptStatus(1);
     if(active_pins & GPIO_PIN4){
         GPIO_clearInterruptFlag(1,GPIO_PIN4);
         if(!GPIO_getInputPinValue(1,GPIO_PIN4)){
                 time[1] = 0;   // Reset seconds
                 time[2]++;     // Increment minutes
                 if(time[2] == 60){  // and so on...
                    time[2] = 0;
                     time[3]++;
                     if(time[3] == 24){
                           time[3] = 0;
                 }
             }
         }
     }
}
