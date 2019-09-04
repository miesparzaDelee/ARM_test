#include <stdint.h>
#include "driverlib/rom.h"

int
main(void)
{
ROM_SysTickPeriodSet(0x1000);
ROM_SysTickEnable();

}
