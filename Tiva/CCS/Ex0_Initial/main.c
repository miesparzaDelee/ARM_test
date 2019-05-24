

/**
 * main.c
 */
int main(void)
{
    *((unsigned int *)0x400FE608U) = 0x20U; // Enable Clock Gating for the port //page 340
       *((unsigned int *)0x40025400U) = 0x0EU; // Set direction (GPIODIR Input or Output)
       *((unsigned int *)0x4002551CU) = 0x0EU; // Set as digital (GPIODEN

       while (1) {
           *((unsigned int *)0x40025038U) = 0x02U;

           int counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

           *((unsigned int *)0x40025038U) = 0x04U;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

           *((unsigned int *)0x40025038U) = 0x08U;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

                   *((unsigned int *)0x40025038U) = 0x0EU;
           counter = 0;
           while (counter < 1000000) {
               ++counter;
           }

       }
}
