/*
 * main.h
 *
 *  Created on: 11/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_

// PIN_ASIGMENTS AND SO
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

// USB DELEE LIBRARY

#define DELEE_USB_BUFFER_SIZE 64
#define DELEE_VID 0xd1ee
#define DELEE_PID 0x0307
#define PRODUCT_STRING_LENGTH (20 + 1) * 2
#define PRODUCT_STRING 'R', 0, 'e', 0, 'l', 0, 'e', 0, 'e', 0, ' ', 0, 'R', 0, 'e', 0, 'm', 0,'o', 0, 't', 0, 'e', 0, 'V', 0, 'a', 0, 'l', 0, 'B', 0, 'o', 0, 'a', 0,'r',0,'d', 0
#include "Delee/usbdDelee.h"

//UART 0 DEBUG
#include "utils/uartstdio.h"
#include "driverlib/uart.h"





#endif /* MAIN_H_ */
