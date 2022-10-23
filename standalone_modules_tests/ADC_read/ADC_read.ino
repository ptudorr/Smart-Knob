#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(500000);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t t;
  int a;
  a=t;
  int x = micros();
  for(int i=0;i<10000;i++)
    system_adc_read_fast(&t, 1,16);
Serial.print(micros()-x);
Serial.print(" ");
Serial.println(t);
}
