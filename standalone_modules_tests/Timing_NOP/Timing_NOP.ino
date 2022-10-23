#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(500000);
}
#define NOP __asm__ __volatile__ ("nop");
#define NOP10 NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP
#define NOP100 NOP10 NOP10 NOP10 NOP10 NOP10 NOP10 NOP10 NOP10 NOP10 NOP10
#define NOP1000 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t t;
  int a;
  a=t;
  int x = micros();
  for(int i=0;i<1000;i++){//620us
    NOP1000}
    //system_adc_read_fast(&t, 1,16);
Serial.print(micros()-x);
Serial.print(" ");
Serial.println(t);
}
