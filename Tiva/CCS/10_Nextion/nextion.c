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

#include "main.h"


volatile uint32_t data1;




int
main(void)
{
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

    while(1)
    {

    }
}

void UART0_IRQHandler(void){
    EUSART_Recive_Tasks();
}

void Nextion_Init(void) {
    EUSART_Init();
//    if (Nextion_Comm_OK()){
//        NEXTION_STATUS=IDDLE;
//        EUSART_Init(nex_mode,nex_mode,BaudRate);
//    }else{
//        NEXTION_STATUS=COMMUNICATIONS_ERROR;
//    }
}

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
UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

// Set the UART to interrupt when half FIFO is ready.
UARTIntClear(UART0_BASE,0xFFFFFFFF);
UARTIntEnable(UART0_BASE, UART_INT_RX);
IntEnable(INT_UART0);

// Enable the UART operation.
 UARTEnable(UART0_BASE);
 RC_POINTER_BUFFER=0;
 }

void EUSART_Recive_Tasks(void) {
             while(UARTCharsAvail(UART0_BASE)){
             RC_PRIVATE_BUFFER[RC_POINTER_BUFFER]=UARTCharGetNonBlocking(UART0_BASE);
             RC_POINTER_BUFFER++;
             }
}

void Nextion_Receive_Main_Tasks() {
    uint8_t counter = 0;
    uint8_t i;
    if(RC_POINTER_BUFFER != 0){
    while (RC_POINTER_BUFFER != counter) {
        if (Nextion_FirstByteValidation(RC_PRIVATE_BUFFER[counter])) {
            switch(IsNextionCommandValid(counter)){
                case 0:
                    counter++;
                    break;
                case 1:
                    for (i=1;i < NEXTION_COMMAND_SIZE-3;i++){
                       NEXTION_COMMAND_ARGS[i-1]=RC_PRIVATE_BUFFER[counter+i];
                    }
                    Nextion_CallBack_Handler(RC_PRIVATE_BUFFER[counter]);
                    counter = counter + NEXTION_COMMAND_SIZE;
                    break;
                case 2:
                    return;
            }
        } else {
            counter++;
        }
    }
    RC_POINTER_BUFFER=0;
}
}

bool Nextion_FirstByteValidation(uint8_t Byte) {
    switch(Byte) {
        case InvalidInstruction:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InstructionSuccessful:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidComponentID:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidPageID:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidPictureID:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidFontID:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidBaudrateSetting:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidWaveformIDorChannel:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidVariableNameorAttribute:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidVariableOperation:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case Assignmentfailedtoassign:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case EEPROMOperationfailed:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case InvalidQuantityofParameters:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case IOOperationfailed:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case EscapeCharacterInvalid:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case VariableNameTooLong:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case SerialBufferOverflow:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case TouchEvent:
            NEXTION_COMMAND_SIZE=7;
            return true;
        case CurrentPageNumber:
            NEXTION_COMMAND_SIZE=5;
            return true;
        case TouchCoordinateAwake:
            NEXTION_COMMAND_SIZE=9;
            return true;
        case TouchCoordinateSleep:
            NEXTION_COMMAND_SIZE=9;
            return true;
        case StringDataEnclosed:
            NEXTION_COMMAND_SIZE=20;
            return true;
        case NumericDataEnclosed:
            NEXTION_COMMAND_SIZE=8;
            return true;
        case AutoEnteredSleepMode:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case AutoWakefromSleep:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case NextionReady:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case StartmicroSDUpgrade:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case TransparentDataFinished:
            NEXTION_COMMAND_SIZE=4;
            return true;
        case TransparentDataReady:
            NEXTION_COMMAND_SIZE=4;
            return true;
        default:
            NEXTION_COMMAND_SIZE=0;
            return false;
    }
}

uint8_t IsNextionCommandValid(uint8_t Buff_pos) {
    if (!(RC_POINTER_BUFFER < NEXTION_COMMAND_SIZE)) {
        if ((0xFFFFFF == RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE-1]) | (RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE - 2] << 8) | (RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE - 2] << 16)) {
            return 1; //Valid Command
        }
    }else{
        return 2; // Buffer not ready
    }
    return 0;//Invalid Command
}

void Nextion_CallBack_Handler(uint8_t CallBackType) {
    switch (CallBackType) {
        case TouchEvent:
           break;
        case CurrentPageNumber:
           break;
         default:
           break;
    }
}
