//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom_map.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"


volatile uint32_t data1;


void EUSART_Init(void);
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``Hello World!''
//! on the UART and is a starting point for more complicated applications.
//!
//! UART0, connected to the Virtual Serial Port and running at
//! 115,200, 8-N-1, is used to display messages from this application.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
//
// Print "Hello World!" to the UART on the evaluation board.
//
//*****************************************************************************
int
main(void)
{
    //volatile uint32_t ui32Loop;

    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //

    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable the GPIO pins for the LED (PF2 & PF3).
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //
    // Initialize the UART.
    EUSART_Init();
    //ConfigureUART();

    UARTEnable(UART0_BASE);

    //
    while(1)
    {
        //
        // Turn on the BLUE LED.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

        //
        // Delay for a bit.
        //
        SysCtlDelay(SysCtlClockGet() / 10 / 3);

        //
        // Turn off the BLUE LED.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

        //
        // Delay for a bit.
        //
        SysCtlDelay(SysCtlClockGet() / 10 / 3);
        while(UARTCharsAvail(UART0_BASE)){
           UARTCharPut(UART0_BASE,UARTCharGetNonBlocking(UART0_BASE));
           }
    }
}

void UART0_IRQHandler(void){
    UARTIntClear(UART0_BASE,
                 UART_INT_RX);

}

//void Nextion_Init(DEV_OPERATION_MODE nex_mode, BAUD_SPEED BaudRate) {
//    delay_ms(400);
//    EUSART_Init(POLLING,POLLING,BaudRate);
//    if (Nextion_Comm_OK()){
//        NEXTION_STATUS=IDDLE;
//        EUSART_Init(nex_mode,nex_mode,BaudRate);
//    }else{
//        NEXTION_STATUS=COMMUNICATIONS_ERROR;
//    }
//}

void EUSART_Init(void){

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

// Configure GPIO Pins for UART mode.
GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

// Use the internal 16MHz oscillator as the UART clock source.
UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
//Initialize USART
UARTConfigSetExpClk(UART0_BASE, 16000000, 115200,
                          (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                           UART_CONFIG_WLEN_8));
//Configure the FIFO registers
UARTFIFOEnable(UART0_BASE);
UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);

// Set the UART to interrupt when half FIFO is ready.
UARTIntClear(UART0_BASE,0xFFFFFFFF);
UARTIntEnable(UART0_BASE, UART_INT_RX);
IntEnable(INT_UART0);

// Enable the UART operation.
 UARTEnable(UART0_BASE);
 }
