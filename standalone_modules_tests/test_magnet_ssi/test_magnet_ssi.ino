// I2C SRF10 or SRF08 Devantech Ultrasonic Ranger Finder
// by Nicholas Zambetti <http://www.zambetti.com>
// and James Tichenor <http://www.jamestichenor.net>

// Demonstrates use of the Wire library reading data from the
// Devantech Utrasonic Rangers SFR08 and SFR10

// Created 29 April 2006

// This example code is in the public domain.

#define CSN 4
#define DO 3
#define CLK 2

void setup() {

  digitalWrite(CSN,HIGH);
  digitalWrite(CLK,HIGH);
  
  pinMode(CLK,OUTPUT);
  pinMode(CSN,OUTPUT);
  pinMode(DO,INPUT);
  
  Serial.begin(9600);          // start serial communication at 9600bps
}

void d(){delayMicroseconds(10);}

byte stat = 0;
void loop() {
  
  digitalWrite(CSN,LOW);
  d();
  int r=0;
  for(int i=0; i<24; i++){
    digitalWrite(CLK,LOW);
    d();
    digitalWrite(CLK,HIGH);
    d();
    //citesc
    if(i<14){
      r = (r<<1)|(digitalRead(DO)==HIGH?1:0);
    }else if(i<18){
      stat = (stat<<1)|(digitalRead(DO)==HIGH?1:0);
    }
  }

  digitalWrite(CSN,HIGH);
  d();

  Serial.print(r*1.0*360.0/16384.0);
  Serial.print(" ");
  Serial.print((stat&0x08)!=0?1:0);
  Serial.print((stat&0x04)!=0?1:0);
  Serial.print((stat&0x02)!=0?1:0);
  Serial.print((stat&0x01)!=0?1:0);
  Serial.println();
  delay(2);
}
