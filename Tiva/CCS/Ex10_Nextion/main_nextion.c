
#include "main.h"

int
main(void)
{

    Main_Init();
    // Initialize the Nextion.
    Nextion_Init();
    if(Nextion_Command("line 20,30,170,200,BLUE")){
        GPIO_PORTF_DATA_BITS_R[LED_WHITE] ^= LED_WHITE;
    }

    while(1)
    {
      Nextion_Receive_Main_Tasks();
    }
}

void UART1_IRQHandler(void){
    Nextion_Recive_Tasks();
    Nextion_Transmit_Tasks();
}

void Nextion_CallBack_Handler(int CallBackType) {
    switch (CallBackType) {
        case TouchEvent:
           GPIO_PORTF_DATA_BITS_R[LED_WHITE] ^= LED_WHITE;
           Nextion_Command("line 20,30,170,200,BLUE");
           return;
        case CurrentPageNumber:
           return;
         default:
           return;
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
