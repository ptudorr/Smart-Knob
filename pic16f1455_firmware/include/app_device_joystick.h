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

#ifndef USBJOYSTICK_H
#define USBJOYSTICK_H

#include <xc.h>
#include "fixed_address_memory.h"
/** TYPE DEFINITIONS ************************************************/
/*typedef union _HAPTIC_IN_CONTROLS_TYPEDEF
{
    struct
    {
        int32_t wheel;
        uint8_t x;
        uint8_t y;
        uint8_t button;
        uint8_t data[9];
    };
    uint8_t val[16];
} HAPTIC_IN_CONTROLS;*/

typedef uint8_t HAPTIC_IN_CONTROLS[16];

/*typedef union _HAPTIC_OUT_CONTROLS_TYPEDEF
{
    uint8_t val[64];
} HAPTIC_OUT_CONTROLS;*/

typedef uint8_t HAPTIC_OUT_CONTROLS[64];

/*typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}RGB;


typedef union _LEDS_CONTROLS_TYPEDEF
{
    struct{
        uint8_t command;
        RGB leds[16];
    };
    uint8_t val[49];
} LEDS_CONTROLS;*/

typedef uint8_t LEDS_CONTROLS[49];

/*typedef union _DISPLAY_CONTROLS_TYPEDEF
{
    uint8_t val[64];
} DISPLAY_CONTROLS;*/
typedef uint8_t DISPLAY_CONTROLS[64];



/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata JOYSTICK_DATA=HAPTIC_IN_DATA_ADDRESS
            HAPTIC_IN_CONTROLS haptic_in;
        #pragma udata
    #elif defined(__XC8)
        HAPTIC_IN_CONTROLS  haptic_in HAPTIC_IN_DATA_ADDRESS;//haptic in
        HAPTIC_OUT_CONTROLS haptic_out HAPTIC_OUT_DATA_ADDRESS;
        LEDS_CONTROLS leds_output LEDS_DATA_ADDRESS;
        DISPLAY_CONTROLS display_output DISPLAY_DATA_ADDRESS;
    #endif
#else
    HAPTIC_IN_CONTROLS haptic_in;
#endif


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
void APP_DeviceJoystickInitialize(void);

/*********************************************************************
* Function: void APP_DeviceJoystickStart(void);
*
* Overview: Starts running the demo.
*
* PreCondition: The device should be configured into the configuration
*   that contains the custome HID interface.  The APP_DeviceJoystickInitialize()
*   function should also have been called before calling this function.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceJoystickStart(void);

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
void APP_DeviceJoystickTasks(void);


#endif