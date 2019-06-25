/*
 * main.h
 *
 *  Created on: 21/05/2019
 *      Author: miesp
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

void Main_Init(void);

#define SW_1    1U
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN
#define SW_2    (1U<<4)


#endif /* MAIN_H_ */
