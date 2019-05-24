
#include "main.h"

int
main(void)
{

    Main_Init();
    // Initialize the Nextion.

    while(1)
    {

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
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_WHITE);
}
