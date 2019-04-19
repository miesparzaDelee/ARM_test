#include <stdint.h>
#include "tm4c123gh6pm.h"

#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)

int main()
{
   
  SYSCTL_RCGCGPIO_R |= (1U<<5);
  GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIO_PORTF_DATA_BITS_R[LED_BLUE]  |= 0xFFFFFFFF;
  while(1){
 GPIO_PORTF_DATA_BITS_R[2] = 0xFFFFFFFF;
 GPIO_PORTF_DATA_BITS_R[2] = 0;
  }
  return 0;
}
