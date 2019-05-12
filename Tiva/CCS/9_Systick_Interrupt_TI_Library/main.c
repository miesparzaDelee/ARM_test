//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
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
#include "delay.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define bool _Bool

#define SYS_CLOCK_HZ 16000000U

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN




int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_WHITE);


    SysTickPeriodSet(SYS_CLOCK_HZ/16U - 1U);
    SysTickEnable();
    SysTickIntEnable();

    while(1){
        /*
       GPIO_PORTF_DATA_BITS_R[LED_WHITE] ^= LED_WHITE;
       delay();
       */
    }

}

void SysTick_Handler(void){
    GPIO_PORTF_DATA_BITS_R[LED_WHITE] ^= LED_WHITE;
}
