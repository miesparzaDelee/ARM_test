
#include "main.h"

int
main(void)
{

    Main_Init();
    // Initialize the Nextion.

    while(1)
    {

        if((GPIO_PIN_4==GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)) || (GPIO_PIN_4==GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0))){
            GPIOPinWrite(GPIO_PORTF_BASE,LED_RED,!LED_RED);
        }else{
            GPIOPinWrite(GPIO_PORTF_BASE,LED_RED,LED_RED);
        }
    }
}


void Main_Init(void){
    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
    // Initialize Stuff
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,LED_RED);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,SW_1);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,SW_2);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
