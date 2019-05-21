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

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_WHITE);

    // Initialize the Nextion.
    Nextion_Init();

    while(1)
    {
      Nextion_Receive_Main_Tasks();
    }
}

void UART1_IRQHandler(void){
    Nextion_Recive_Tasks();
}


void Nextion_Init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

// Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

// Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
//Initialize USART
    UARTConfigSetExpClk(UART1_BASE, 16000000, 115200,
                        (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_WLEN_8));
//Configure the FIFO registers
    UARTFIFOEnable(UART1_BASE);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);

// Set the UART to interrupt when half FIFO is ready.
    UARTIntClear(UART1_BASE, 0xFFFFFFFF);
    UARTIntEnable(UART1_BASE, UART_INT_RX);
    IntEnable(INT_UART1);

// Enable the UART operation.
    UARTEnable(UART1_BASE);
    RC_POINTER_BUFFER = 0;
    TX_POINTER_BUFFER = 0;
    TX_ACTUAL_WRITE = 0;
}

void Nextion_Recive_Tasks(void)
{
     // if (TXIF) {
    while (UARTCharsAvail(UART1_BASE))
    {
        RC_PRIVATE_BUFFER[RC_POINTER_BUFFER] = UARTCharGetNonBlocking(
                UART1_BASE);
        RC_POINTER_BUFFER++;
    }
        // }
}

void EUSART_Transmit_Tasks(void)
{
    // if (TXIF) {
    if (TX_POINTER_BUFFER > 0)
    {

        if (UARTCharPutNonBlocking(UART1_BASE,
                                   TX_PRIVATE_BUFFER[TX_ACTUAL_WRITE]))
        {
            TX_ACTUAL_WRITE++;
        }
    }
    if (TX_POINTER_BUFFER == TX_ACTUAL_WRITE)
    {
        //PIE1bits.TXIE = 0; // Disable interrupts
        TX_POINTER_BUFFER = 0;
        TX_ACTUAL_WRITE = 0;
    }
    // }
}

bool EUSART_Transmit_Buffer(uint8_t *Buffer, int max)
{
    //Basic Transmition
    bool SaveInt;
    int count = 0;
    while (count < max)
    {
        if (EUSART_Transmit_Byte(*Buffer) != true)
            return false;
        Buffer++;
        count++;

    }
    return true;
}

bool EUSART_Transmit_Byte(uint8_t Character)
{
    if (TX_POINTER_BUFFER < TX_PRIVATE_BUFFER_LENGTH)
    {
        TX_PRIVATE_BUFFER[TX_POINTER_BUFFER] = Character;
        TX_POINTER_BUFFER++;
        // PIE1bits.TXIE=1; Enable Interrupt

        return 1;
    }
    else
    {
        return 0;
    }
}


void Nextion_Receive_Main_Tasks(void)
{
    int counter = 0;
    int i;
    if (RC_POINTER_BUFFER != 0)
    {
        while (RC_POINTER_BUFFER != counter)
        {
            if (Nextion_FirstByteValidation(RC_PRIVATE_BUFFER[counter]))
            {
                switch (IsNextionCommandValid(counter))
                {
                case 0:
                    counter++;
                    break;
                case 1:
                    for (i = 1; i < NEXTION_COMMAND_SIZE - 3; i++)
                    {
                        NEXTION_COMMAND_ARGS[i - 1] = RC_PRIVATE_BUFFER[counter
                                + i];
                    }
                    Nextion_CallBack_Handler(RC_PRIVATE_BUFFER[counter]);
                    counter = counter + NEXTION_COMMAND_SIZE;
                    break;
                case 2:
                    while (UARTCharsAvail(UART1_BASE))
                    {
                        RC_PRIVATE_BUFFER[RC_POINTER_BUFFER] =
                                UARTCharGetNonBlocking(
                                UART1_BASE);
                        RC_POINTER_BUFFER++;
                    }
                    return;
                }
            }
            else
            {
                counter++;
            }
        }
        RC_POINTER_BUFFER = 0;
    }
}

bool Nextion_FirstByteValidation(int Byte) {
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

int IsNextionCommandValid(int Buff_pos) {
    if (!(RC_POINTER_BUFFER < (NEXTION_COMMAND_SIZE))) {
        if ((0xFFFFFF == RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE-1]) | (RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE - 2] << 8) | (RC_PRIVATE_BUFFER[Buff_pos + NEXTION_COMMAND_SIZE - 2] << 16)) {
            return 1; //Valid Command
        }
    }else{
        return 2; // Buffer not ready
    }
    return 0;//Invalid Command
}

void Nextion_CallBack_Handler(int CallBackType) {
    switch (CallBackType) {
        case TouchEvent:
           GPIO_PORTF_DATA_BITS_R[LED_WHITE] ^= LED_WHITE;
           return;
        case CurrentPageNumber:
           return;
         default:
           return;
    }
}
