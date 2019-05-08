/*
 * delay.c
 *
 *  Created on: 07/05/2019
 *      Author: miesp
 */
#include "delay.h"

void delay(void){
    int counter = 0;
    while (counter < 1000000) {
                   ++counter;
               }
}
