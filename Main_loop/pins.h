#ifndef __PINS_H_INCLUDED
#define __PINS_H_INCLUDED

#define LED_PIN 100
#define PIC_CS_PIN 15
#define DISPLAY_CS_PIN 2 //HIGH at boot connected to on-board LED, boot fails if pulled LOW
#define DISPLAY_DC_PIN MCU_MISO_PIN //D/C on MISO
#define MCU_MISO_PIN 12
#define MCU_MOSI_PIN 13
#define MCU_CLK_PIN 14

#endif
