
#include <Arduino.h>
#include "USB.h"
#include <SPI.h>

#define DEBUG_TRANSACTION
#define USB_WAIT_MICROS 25
#define BEGIN_TRANSFER 0x55
#define ACK1 0x76

#define REQUEST_HAPTIC_IN 0x01

uint8_t haptic_IN_buffer[HAPTIC_IN_BUFFER_SIZE];
uint8_t luminosity;//first control byte to send
uint8_t errors_ctr2_to_PIC;//second control byte to send

void USB(){
  //receive/send usb packet
  #ifdef DEBUG_TIMING
    pu=!pu;digitalWrite(4,pu);
  #endif
  
  SPI.begin();//make sure SPI.begin() has been called
  SPI.beginTransaction(SPISettings(6000000, MSBFIRST, SPI_MODE0));//lower SPI bitrate
  GPOC = (1<<PIC_CS_PIN); //CS = LOW; select the PIC
  int nr=0;
  while(1){
    uint8_t rec = SPI.transfer(BEGIN_TRANSFER);//send a byte announcing a request
    if(rec == ACK1){             //response from PIC - ACK1
      #ifdef DEBUG_TRANSACTION
        Serial.print("GOT RESPONSE ");Serial.print(rec,HEX);Serial.println("|");
      #endif
      break;
    } 
    nr++;                         //for timeout functionality
    delayMicroseconds(1);     //wait a bit to allow PIC to finish current action
    if(nr==USB_WAIT_MICROS) {     //timeout
      #ifdef DEBUG_TRANSACTION
        Serial.print(rec);Serial.println("TIMEOUT");
      #endif
      break;}
  }
  if(nr==USB_WAIT_MICROS){
    //we have a timeout
    SPI.transfer(0x00);
    //signal that the possible transmitted ACK1 will not be taken into consideration
  }else{
    //we have received ACK; the PIC is ready to comunicate

    //we now have to exchange 2 control bytes
    uint8_t pkt_requests;//bitmask for each packet type
    uint8_t ctrl2_from_PIC;//second ctrl byte
    
    delayMicroseconds(1);
    pkt_requests = SPI.transfer(luminosity);
    delayMicroseconds(1);
    ctrl2_from_PIC = SPI.transfer(errors_ctr2_to_PIC);
    
    
    if(pkt_requests & REQUEST_HAPTIC_IN){
      //send HAPTIC_IN_BUFFER_SIZE bytes
      
      /*for(int i=0;i<HAPTIC_IN_BUFFER_SIZE;i++){
        delayMicroseconds(1);
        SPI.transfer(haptic_IN_buffer[i]);
      }*/
      //same as above but with pointers
      for(uint8_t *p=haptic_IN_buffer; p < haptic_IN_buffer+HAPTIC_IN_BUFFER_SIZE; p++){
        delayMicroseconds(1);
        //we can wait 16us total since the packet is 4 times smaller than the others
        SPI.transfer(*p);
      }
      //empty the send/receive buffer
      delayMicroseconds(1);
      SPI.transfer(0x00);
    }else{
      //become slave, then receive 49-64 bytes
    }
    
    
  }//end received ACK
  
  GPOS = (1<<PIC_CS_PIN); //CS = HIGH; deselect the PIC

  #ifdef DEBUG_TIMING
    delayMicroseconds(175);
  #endif
}
