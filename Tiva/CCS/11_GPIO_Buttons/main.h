/*
 * main.h
 *
 *  Created on: 11/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_


//#define LOADCELL_SPEED
#define LOADCELL_DOUT GPIO_PIN_0
#define LOADCELL_CLK GPIO_PIN_1
#include "Delee/LoadCell.h"


// USB DELEE LIBRARY
#define DELEE_USB_BUFFER_SIZE 256
#define DELEE_VID 0xd1ee
#define DELEE_PID 0x0303
#define PRODUCT_STRING_LENGTH (20 + 1) * 2
#define PRODUCT_STRING 'G', 0, 'e', 0, 'n', 0, 'e', 0, 'r', 0, 'i', 0, 'c', 0, ' ', 0, 'D', 0,'e', 0, 'l', 0, 'e', 0, 'e', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0,'c',0,'e', 0
#include "Delee/usbdDelee.h"

//UART 0 DEBUG
#include "utils/uartstdio.h"
#include "driverlib/uart.h"



#endif /* MAIN_H_ */
