/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

#ifndef USBJOYSTICK_C
#define USBJOYSTICK_C

/** INCLUDES *******************************************************/
#include "include/usb/usb.h"
#include "include/usb/usb_device_hid.h"
#include "include/app_device_joystick.h"

#include "include/system.h"

#include "include/app_led_usb_status.h"
#include "include/spi.h"

#include "stdint.h"

/** DECLARATIONS ***************************************************/
//http://www.microsoft.com/whdc/archive/hidgame.mspx
#define HAT_SWITCH_NORTH            0x0
#define HAT_SWITCH_NORTH_EAST       0x1
#define HAT_SWITCH_EAST             0x2
#define HAT_SWITCH_SOUTH_EAST       0x3
#define HAT_SWITCH_SOUTH            0x4
#define HAT_SWITCH_SOUTH_WEST       0x5
#define HAT_SWITCH_WEST             0x6
#define HAT_SWITCH_NORTH_WEST       0x7
#define HAT_SWITCH_NULL             0x8




USB_VOLATILE USB_HANDLE last_HAP_IN = 0;
USB_VOLATILE USB_HANDLE last_HAP_OUT = 0;
USB_VOLATILE USB_HANDLE last_LED_OUT = 0;
USB_VOLATILE USB_HANDLE last_DSP_OUT = 0;


/*********************************************************************
* Function: void APP_DeviceJoystickInitialize(void);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceJoystickInitialize(void)
{  
    //initialize the variable holding the handle for the last
    // transmission
    last_HAP_IN = 0;
    last_HAP_OUT = 0;
    last_LED_OUT = 0;
    last_DSP_OUT = 0;

    //enable the HID endpoint
    USBEnableEndpoint(HAPTIC_EP,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(LEDS_EP  ,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(DISPLAY_EP  ,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
}//end UserInit

/*********************************************************************
* Function: void APP_DeviceJoystickTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceJoystickInitialize() and APP_DeviceJoystickStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/

uint8_t cntr=0;

void APP_DeviceJoystickTasks(void)
{  
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        /* Jump back to the top of the while loop. */
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended() == true )
    {
        /* Jump back to the top of the while loop. */
        return;
    }

    //If the last transmission is complete
    if(!HIDTxHandleBusy(last_HAP_IN))
    {
        //If the button is pressed
        if(/*BUTTON_IsPressed(BUTTON_USB_DEVICE_HID_JOYSTICK)*/false == true)
        {
            //Indicate that the "x" button is pressed, but none others

            //Move the hat switch to the "east" position
            //haptic_in.button = HAT_SWITCH_EAST;

            haptic_in[1] = TESTB;
            //Move the X and Y coordinates to the their extreme values (0x80 is
            //  in the middle - no value).
            //joystick_input.members.analog_stick.X = 0;
            //joystick_input.members.analog_stick.Y = 0;

            //Send the packet over USB to the host.
            last_HAP_IN = HIDTxPacket(HAPTIC_EP, (uint8_t*)&haptic_in, sizeof(haptic_in));

        }
        else
        {
            //Reset values of the controller to default state

            //Buttons
            //haptic_in.val[0] = cntr++;
            //haptic_in.val[1] = TESTB;
            
            haptic_in[0] = display_output[0];
            haptic_in[1] = display_output[1];
            haptic_in[2] = TESTB;
            haptic_in[3] = SSPCON1;
            haptic_in[4] = SSPSTAT;
            haptic_in[5] = display_output[63];

            //Hat switch
            //haptic_in.val[2] = haptic_out.val[3];

            //Analog sticks
            

            //Send the 8 byte packet over USB to the host.
            last_HAP_IN = HIDTxPacket(HAPTIC_EP, (uint8_t*)&haptic_in, sizeof(haptic_in));
        }
    }
    
    if(!HIDRxHandleBusy(last_HAP_OUT)){
        last_HAP_OUT = HIDRxPacket(HAPTIC_EP, (uint8_t*)&haptic_out, sizeof(haptic_out));
    }
    if(!HIDRxHandleBusy(last_DSP_OUT)){
        last_DSP_OUT = HIDRxPacket(DISPLAY_EP, (uint8_t*)&display_output, sizeof(display_output));
    }
    if(!HIDRxHandleBusy(last_LED_OUT)){
        /*if(leds_output.val[48] == 0x97)
            LED_On(LED_D3);
        else
            LED_Off(LED_D3);*/
        last_LED_OUT = HIDRxPacket(LEDS_EP, (uint8_t*)&leds_output, sizeof(leds_output));
    }
    
}//end ProcessIO

#endif
