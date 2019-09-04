/*
 * main.h
 *
 *  Created on: Jun 17, 2019
 *      Author: franc
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define DELEE_USB_BUFFER_SIZE 64
#define DELEE_VID 0xd1ee
#define DELEE_PID 0x0307
#define PRODUCT_STRING_LENGTH (20 + 1) * 2
#define PRODUCT_STRING 'R', 0, 'e', 0, 'l', 0, 'e', 0, 'e', 0, ' ', 0, 'R', 0, 'e', 0, 'm', 0,'o', 0, 't', 0, 'e', 0, 'V', 0, 'a', 0, 'l', 0, 'B', 0, 'o', 0, 'a', 0,'r',0,'d', 0


#define USE_REMOTE_VALVE_USB
#define USE_REMOTE_VALVE_USB_CALLBACK

#define RV_CHANNEL_1   PIN_B6  // GPIO_PORTB_BASE+(GPIO_PIN_6<<2)
#define RV_CHANNEL_2   PIN_B7  //    GPIO_PORTB_BASE+(GPIO_PIN_7<<2)
#define RV_CHANNEL_3   PIN_B2  //     GPIO_PORTB_BASE+(GPIO_PIN_2<<2)
#define RV_CHANNEL_4   PIN_B3  //     GPIO_PORTB_BASE+(GPIO_PIN_3<<2)
#define RV_CHANNEL_5   PIN_A4  //      GPIO_PORTA_BASE+(GPIO_PIN_4<<2)
#define RV_CHANNEL_6   PIN_A3  //     GPIO_PORTA_BASE+(GPIO_PIN_3<<2)
#define RV_CHANNEL_7   PIN_A2  //         GPIO_PORTA_BASE+(GPIO_PIN_2<<2)
#define RV_CHANNEL_8   PIN_C7  //          GPIO_PORTC_BASE+(GPIO_PIN_7<<2)

#define RV_BUTTON_1 PIN_A5 //GPIO_PORTA_BASE+(GPIO_PIN_5<<2)
#define RV_BUTTON_2 PIN_A6 //GPIO_PORTA_BASE+(GPIO_PIN_6<<2)
#define RV_BUTTON_3 PIN_A7 //GPIO_PORTA_BASE+(GPIO_PIN_7<<2)
#define RV_BUTTON_4 PIN_D2 //GPIO_PORTD_BASE+(GPIO_PIN_2<<2)
#define RV_BUTTON_5 PIN_D3 //GPIO_PORTD_BASE+(GPIO_PIN_3<<2)
#define RV_BUTTON_6 PIN_E1 //GPIO_PORTE_BASE+(GPIO_PIN_1<<2)
#define RV_BUTTON_7 PIN_E2 //GPIO_PORTE_BASE+(GPIO_PIN_2<<2)
#define RV_BUTTON_8 PIN_E3 //GPIO_PORTE_BASE+(GPIO_PIN_3<<2)

#include <RemoteValve.h>




#endif /* MAIN_H_ */
