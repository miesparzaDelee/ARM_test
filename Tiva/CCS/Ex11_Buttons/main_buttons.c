
#include "main.h"
int32_t aa;
int
main(void)
{
    Main_Init();
    // Initialize the Nextion.

    while(1)
    {
        if((0==GPIOPinRead(GPIO_PORTF_BASE,SW_1))||(0==GPIOPinRead(GPIO_PORTF_BASE,SW_2))){
            GPIOPinWrite(GPIO_PORTF_BASE,LED_WHITE,LED_RED);
        }else{
            GPIOPinWrite(GPIO_PORTF_BASE,LED_WHITE,0);
        }
    }
}

uint8_t a;
void Main_Init(void){
    //
    // Set the clocking to run directly from the crystal.
    //


    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    HWREG(GPIO_PORTC_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTC_BASE+GPIO_O_CR) |= (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE+GPIO_O_CR) |= GPIO_PIN_7;
    // Initialize Stuff


    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,LED_RED);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,SW_1|SW_2);
    GPIOPadConfigSet(GPIO_PORTF_BASE,SW_1|SW_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

}
