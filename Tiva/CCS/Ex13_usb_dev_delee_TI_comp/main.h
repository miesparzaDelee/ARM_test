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
