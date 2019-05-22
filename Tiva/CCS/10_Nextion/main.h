/*
 * main.h
 *
 *  Created on: 21/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "inc/tm4c123gh6pm.h"
#include "Delee/Nextion.h"

void Main_Init(void);

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN



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
