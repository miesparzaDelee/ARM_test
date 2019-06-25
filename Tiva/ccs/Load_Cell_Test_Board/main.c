
#include "main.h"

/**
 * main.c
 */

// Enable the GPIOB peripheral
int32_t i32Val;
//
// Enable the GPIOA peripheral
//

//
// Wait for the GPIOA module to be ready.
//
#define bool _Bool
#define SYS_CLOCK_HZ 16000000U

//**********************************************************************************//

int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){
    }

    ConfigureUART();
    UARTprintf("Inicio\n");
    IntMasterEnable();
    SysTickIntEnable();
    SysTickPeriodSet(SYS_CLOCK_HZ/10);
    SysTickEnable();

    HX711_Init(A_128);
    int32_t Contador_print = 0;

    while(1){
        HX711_Main_Tasks();
        if (Contador_print >= 815000) { //815000 para 4s
        UARTprintf("Valor RAW:%d\n", HX711_DISPLAY_VALUE);
        UARTprintf("Valor en gramos:%d\n", VALUE_GRAMS);
        UARTprintf("Valor de flujo:%d\n", FLOW_FILTRADO);
        UARTprintf("-------------------------------------- %d\n");
        Contador_print = 0;
        } else {
            Contador_print++;
        }
    }
    return 0;
}


void delay(void){
    int counter = 0;
    while (counter < 500000) {
                   ++counter;
               }
}


void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

void SysTick_Handler(void){
    //UARTprintf("Interrupt\n");
    Flow_Value();
}
