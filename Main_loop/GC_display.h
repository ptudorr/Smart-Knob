#ifndef __GC_DISPLAY_H_INCLUDED
#define __GC_DISPLAY_H_INCLUDED


/**
 * ******************** PINOUT ********************
 * GC9A01                                    NodeMCU
 * CS                                       GPIO2
 * SCL                                      SCK(GPIO14)
 * SDA                                      MOSI(GPIO13)
 * D/C                                      MISO(GPIO12)//a trick to reuse MISO
 * RES                                      RST(NodeMCU reset pin)
 * BRIGHTNESS TO PIC                          X
 */

#include "pins.h"
#include <Arduino.h>

#define DISPLAY_OUT_BUFFER_SIZE 64

extern uint32_t pd;

extern uint8_t display_OUT_buffer[DISPLAY_OUT_BUFFER_SIZE];

void updateDisplay();

void initializeDisplay();



#endif
