// PIN_ASIGMENTS AND SO
#include "main.h"

void ConfigureUART(void);

#define SYS_CLOCK_HZ 16000000U


int main(void)
 {
   ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                             SYSCTL_XTAL_16MHZ);
   RV_Init();
   Configure_Pin(PIN_F3, 1);


//    UARTprintf("System Initialized \n");

    while (1)
    {
        RV_Main_Tasks();
        if(USB_CONNECTED){
            Output(PIN_F3,1);
        }else{
            Output(PIN_F3,0);
        }
    }
}


bool RV_Board_Identify(void){

    return 1;
}
