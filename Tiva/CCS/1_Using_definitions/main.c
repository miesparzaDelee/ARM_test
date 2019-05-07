

/**
 * main.c
 */
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN

int main(void)
{
    SYSCTL_RCGCGPIO_R=(1U<<5);   // Enable Clock Gating for the port //page 340
    //*((unsigned int *)0x400FE608U) = 0x20U; // Enable Clock Gating for the port //page 340
    GPIO_PORTF_DIR_R = 0x0EU;
    //*((unsigned int *)0x40025400U) = 0x0EU; // Set direction (GPIODIR Input or Output)
    GPIO_PORTF_DEN_R = 0x0EU;
       //*((unsigned int *)0x4002551CU) = 0x0EU; // Set as digital (GPIODEN

       while (1) {
           GPIO_PORTF_DATA_R = LED_RED;

           int counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

           GPIO_PORTF_DATA_R = LED_BLUE;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

           GPIO_PORTF_DATA_R = LED_GREEN;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

           GPIO_PORTF_DATA_R = LED_WHITE;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

       }
}