#ifndef __USB_H_INCLUDED
#define __USB_H_INCLUDED

#include "pins.h"
#include <Arduino.h>

#define HAPTIC_IN_BUFFER_SIZE 16

extern uint32_t pu;
extern uint8_t luminosity;//first control byte to send
extern uint8_t errors_ctr2_to_PIC;//second control byte to send

extern uint8_t haptic_IN_buffer[HAPTIC_IN_BUFFER_SIZE];

void USB();






#endif
