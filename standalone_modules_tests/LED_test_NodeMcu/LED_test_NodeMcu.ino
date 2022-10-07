#include <ESP8266WiFi.h>
#define NO_CORRECTION 1
#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 16
#define DATA_PIN 3



CRGB leds[NUM_LEDS];

/*typedef struct{
  uint8_t r;
  uint8_t g;
  uint8_t b;
}color;


color red = {255,0,0};
color grn = {0,255,0};
color blu = {0,0,255};
const color colarray[16] = {red,grn,blu,red,grn,blu,red,grn,blu,red,grn,blu,red,grn,blu,{255,255,255}};*/

void sendToLED(){
  
  register uint8_t i=0;
  while(1){
    /*digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(4);
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(2);*/

  WRITE_PERI_REG(0x60000300,i);
  delayMicroseconds(1);
  //WRITE_PERI_REG(0x60000300,0x0000);
  //delayMicroseconds(10);
  i+=32;
  }
}

void setup() {
  // put your setup code here, to run once:
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
  
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  /*pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);*/
  //FastLED.setMaxRefreshRate(0,false);

}

uint8_t c=0,d=1;

void loop() {
  c+=d;
  if(c==0)d=1;
  if(c==255)d=-1;
  // put your main code here, to run repeatedly:
  for(int i=0;i<16;i++)
    leds[i] = c*256*256+c*256+2*c/3;
  FastLED.show();
  //delayMicroseconds(100);
  // Now turn the LED off, then pause
  /*for(int i=0;i<16;i++)
    leds[i] = CRGB::Blue;
  FastLED.show();*/
  //delayMicroseconds(100);
  //sendToLED();
}
