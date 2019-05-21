/*
 * main.h
 *
 *  Created on: 21/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom_map.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN

#ifndef RC_PRIVATE_BUFFER_LENGTH
#define RC_PRIVATE_BUFFER_LENGTH 200
#endif

#ifndef TX_PRIVATE_BUFFER_LENGTH
#define TX_PRIVATE_BUFFER_LENGTH 200
#endif

volatile int RC_POINTER_BUFFER;
volatile int NEXTION_COMMAND_SIZE;
volatile int RC_PRIVATE_BUFFER[RC_PRIVATE_BUFFER_LENGTH];
volatile int NEXTION_COMMAND_ARGS[10];

volatile int TX_POINTER_BUFFER;
volatile int  TX_ACTUAL_WRITE;
volatile uint8_t TextValue[10];
volatile uint8_t CommandString[30];
volatile uint8_t TX_PRIVATE_BUFFER[TX_PRIVATE_BUFFER_LENGTH];

#define InvalidInstruction               0x00
#define InstructionSuccessful            0x01
#define InvalidComponentID               0x02
#define InvalidPageID                    0x03
#define InvalidPictureID                 0x04
#define InvalidFontID                    0x05
#define InvalidBaudrateSetting           0x11
#define InvalidWaveformIDorChannel       0x12
#define InvalidVariableNameorAttribute   0x1A
#define InvalidVariableOperation         0x1B
#define Assignmentfailedtoassign         0x1C
#define EEPROMOperationfailed            0x1D
#define InvalidQuantityofParameters      0x1E
#define IOOperationfailed                0x1F
#define EscapeCharacterInvalid           0x20
#define VariableNameTooLong              0x23
/* </editor-fold>*/

/*Nextion Event Values (NO - BKCMD)*/
#define SerialBufferOverflow             0x24
#define TouchEvent                       0x65
#define CurrentPageNumber                0x66
#define TouchCoordinateAwake             0x67
#define TouchCoordinateSleep             0x68
#define StringDataEnclosed               0x70
#define NumericDataEnclosed              0x71
#define AutoEnteredSleepMode             0x86
#define AutoWakefromSleep                0x87
#define NextionReady                     0x88
#define StartmicroSDUpgrade              0x89
#define TransparentDataFinished          0xFD
#define TransparentDataReady             0xFE


void Nextion_Init(void);
void Nextion_Recive_Tasks(void);
bool Nextion_FirstByteValidation(int Byte);
int IsNextionCommandValid(int Buff_pos);
void Nextion_CallBack_Handler(int CallBackType);
bool EUSART_Transmit_Buffer(uint8_t *Buffer, int max);
void EUSART_Transmit_Tasks(void);
bool EUSART_Transmit_Byte(uint8_t Character);

//Delee libraries
typedef enum {
    OFF=0, // Not initialized
    DISCONNECTED = 1,
    IDDLE = 2,
    REESTART = 3,
    STARTED = 4,
    WRITTING_DATA = 5,
    READING_DATA = 6,
    ENDING_COMM = 7,
    COMMUNICATIONS_ERROR = 8,
    NOT_AVAILABLE = 9,
} DEV_STATUS;

typedef enum {
    POLLING,
    EXT_POLLING,
    INTERRUPT_HIGH,
    INTERRUPT_LOW,
} DEV_OPERATION_MODE;

#endif /* MAIN_H_ */
