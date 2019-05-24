#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "delay.h"

#define SYS_CLOCK_HZ 16000000U

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN

int main(void)
{
    SYSCTL -> RCGCGPIO = (1U<<5); // Enable Clock Gating for the port //page 340
    GPIOF -> DIR = 0x0EU; // Set direction (GPIODIR Input or Output)
    GPIOF -> DEN = 0x0EU; // Set as digital output

    SysTick -> LOAD = SYS_CLOCK_HZ/16U - 1U;
    SysTick -> VAL = 0U;
    SysTick -> CTRL = (1U << 2) | (1U << 1) | (1U);

    __enable_irq();

    while(1){
        // Polling code
       // GPIOF->DATA_Bits[LED_WHITE] ^= LED_WHITE;
      // delay();
    }

}

void SysTick_Handler(void){
    GPIOF->DATA_Bits[LED_WHITE] ^= LED_BLUE;
}
