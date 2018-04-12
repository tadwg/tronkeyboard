/*******************************************************************************
  Main Demo File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Main demo file for keyboard project.  Entry point for compiler.

  Description:
    Main demo file for keyboard project.  Entry point for compiler.  Also
    calls the system initailization and handles system issues like calling the
    demo code appropriately and handing device level events from the USB stack.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* Standard C includes */
#include <stdint.h>

/* Microchip library includes */
#include <system.h>
#include <system_config.h>

#include <usb/usb.h>
#include <usb/usb_device_hid.h>

/* Demo project includes */
//#include "app_led_usb_status.h"
#include "app_device_keyboard.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************


int	main(void)
{
	SYSTEM_Initialize(SYSTEM_STATE_USB_START);
	
	USBDeviceInit();
	USBDeviceAttach();
	
	for (;;) {
		SYSTEM_Tasks();
#ifdef	USB_POLLING
		USBDeviceTasks();
#endif
		if (USBGetDeviceState() < CONFIGURED_STATE)
			continue;
		if (USBIsDeviceSuspended() == true)
			continue;
		APP_KeyboardTasks();
	}
}



bool	USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
	switch ((int)event) {
		case EVENT_TRANSFER:
			break;
		case EVENT_SOF:
			keyscan();
			break;
		case EVENT_SUSPEND:
			break;
		case EVENT_RESUME:
			break;
		case EVENT_CONFIGURED:
			APP_KeyboardInit();
			break;
		case EVENT_SET_DESCRIPTOR:
			break;
		case EVENT_EP0_REQUEST:
			USBCheckHIDRequest();
			break;
		case EVENT_BUS_ERROR:
			break;
		case EVENT_TRANSFER_TERMINATED:
			break;
	}
	return true;
}

/*******************************************************************************
 End of File
*/
