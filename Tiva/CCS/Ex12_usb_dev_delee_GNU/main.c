

#include "main.h"


//*****************************************************************************
//
// Flags used to pass commands from interrupt context to the main loop.
//
//*****************************************************************************
/*#define COMMAND_PACKET_RECEIVED 0x00000001
#define COMMAND_STATUS_UPDATE   0x00000002

volatile uint32_t g_ui32Flags = 0;
*/
//*****************************************************************************
//
// Receive new data and echo it back to the host.
//
// \param psDevice points to the instance data for the device whose data is to
// be processed.
// \param pui8Data points to the newly received data in the USB receive buffer.
// \param ui32NumBytes is the number of bytes of data available to be processed.
//
// This function is called whenever we receive a notification that data is
// available from the host. We read the data, byte-by-byte and swap the case
// of any alphabetical characters found then write it back out to be
// transmitted back to the host.
//
// \return Returns the number of bytes of data processed.
//


//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// This is the main application entry function.
//
//*****************************************************************************
int
main(void)
{

    //
    // Set the clocking to run from the PLL at 50MHz
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    //
    // Open UART0 and show the application name on the UART.
    //
    ConfigureUART();

    UARTprintf(" Tiva C USB Delee device example\n");
    UARTprintf("---------------------------------\n\n");
    //
    // Open UART0 and show the application name on the UART.
    //
    USB_Delee_Init();
    UARTprintf("Configuring USB\n");
    bool usb_previous = ~USB_CONNECTED;
    while(1)
    {

        USB_Delee_Main_Tasks();
        if (usb_previous != USB_CONNECTED){
        if(USB_CONNECTED){

            UARTprintf("USB_Connected...\n");
                }else{
                    UARTprintf("USB_Disonnected...\n");
                }
        }
        usb_previous=USB_CONNECTED;
    }
    }


void USB_Delee_Command_CallBack(uint16_t Command, uint8_t Instance){

}

void UART0_IRQHandler(void){
   // UARTStdioIntHandler();
}
 void USB0_IRQHandler(void){
     USB0DeviceIntHandler();
 }
