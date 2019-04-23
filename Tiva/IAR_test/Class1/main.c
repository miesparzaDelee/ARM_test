#include <stdint.h>
#include "tm4c123gh6pm.h"

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)

void delay(int value);

void delay(int value){
int volatile counter=0;
while (counter<value){
  counter++;
}
}  

int main()
{
   
  SYSCTL_RCGCGPIO_R |= (1U<<5);
  GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIO_PORTF_DATA_BITS_R[LED_BLUE]  |= 0xFFFFFFFF;
  
  
  while(1){
 GPIO_PORTF_DATA_BITS_R[2] = 0xF;
 delay(100000);
 GPIO_PORTF_DATA_BITS_R[2] = 0;
 delay(100000);
  }
  return 0;
}
