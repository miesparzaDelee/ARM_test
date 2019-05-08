#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "delay.h"

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN

typedef struct {
    uint16_t x;
    uint8_t y;
}Point;

typedef struct{
    Point top_left;
    Point bottom_right;
} Window;

typedef struct{
    Point corners[3];
} Triangle;

Point pa,pb;

Window wa;


int main(void)
{

    pa.x = sizeof(Point);
    pa.y = pa.x+3U;

    Point *pp;
    Window *pw;
    pp = &pa;
    pw = &wa;

    pp -> x = 2U;
    pw -> bottom_right = *pp;

    // Using CMSIS standard structures pointers to access and configure hardware

    SYSCTL -> RCGCGPIO = (1U<<5); // Replaces SYSCTL_RCGCGPIO_R=(1U<<5);// Enable Clock Gating for the port //page 340

    GPIOF -> DIR = 0x0EU; // Replaces GPIO_PORTF_DIR_R = 0x0EU; // Set direction (GPIODIR Input or Output)

    GPIOF -> DEN = 0x0EU; // Replaces GPIO_PORTF_DEN_R = 0x0EU; // Set as digital output

     while (1) {

         GPIOF->DATA_Bits[LED_WHITE]=LED_RED;
         delay();

         GPIOF->DATA_Bits[LED_WHITE]=LED_BLUE;
         delay();

         GPIOF->DATA_Bits[LED_WHITE]=LED_GREEN;
         delay();

         GPIOF->DATA_Bits[LED_WHITE]=LED_WHITE;
         delay();

       }
}
