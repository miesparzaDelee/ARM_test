/*
 * main.h
 *
 *  Created on: 21/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_

#ifndef RC_PRIVATE_BUFFER_LENGTH
#define RC_PRIVATE_BUFFER_LENGTH 200
#endif

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

volatile uint32_t RC_POINTER_BUFFER;
volatile uint8_t NEXTION_COMMAND_SIZE;
volatile uint8_t RC_PRIVATE_BUFFER[RC_PRIVATE_BUFFER_LENGTH];
volatile uint8_t NEXTION_COMMAND_ARGS[10];

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


void EUSART_Init(void);
void Nextion_Init(void);
void EUSART_Recive_Tasks(void);
bool Nextion_FirstByteValidation(uint8_t Byte);
uint8_t IsNextionCommandValid(uint8_t Buff_pos);
void Nextion_CallBack_Handler(uint8_t CallBackType);

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
