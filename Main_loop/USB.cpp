
#include <Arduino.h>
#include "USB.h"
#include "buffers.h"
#include <SPI.h>

//#define DEBUG_TRANSACTION
//#define DEBUG_TIMEOUT //print timeout message
#define USB_WAIT_MICROS 40
#define BEGIN_TRANSFER 0x55
#define ACK1 0x76

//OUT_type 2 bits, IS_OUT 1 bit, IS_IN1 bit
#define REQUEST_HAPTIC_IN   0x01  //0001
#define REQUEST_OUT         0x02  //0010
#define REQUEST_HAPTIC_OUT  0x06  //0110
#define REQUEST_LED_OUT     0x0A  //1010
#define REQUEST_DISPLAY_OUT 0x0E  //1110

#define GET_TRANSFER_NUMBER (((ESP8266_REG(0x100+4*12))>>23)&0xf)
#define copyPKT(pkt,nr) pkt[nr] = SPI1W##nr

uint8_t haptic_IN_buffer[HAPTIC_IN_BUFFER_SIZE];
uint8_t luminosity;//first control byte to send
uint8_t errors_ctr2_to_PIC;//second control byte to send

uint16_t cntrusb;

uint32_t TESTPKT[16];
uint8_t received = 0;

void pinSpecialFast(uint8_t pin) {
      GPC(pin) = (GPC(pin) & (0xF << GPCI)); //SOURCE(GPIO) | DRIVER(NORMAL) | INT_TYPE(UNCHANGED) | WAKEUP_ENABLE(DISABLED)
      GPEC = (1 << pin); //Disable
      GPF(pin) = GPFFS(GPFFS_BUS(pin));//Set mode to BUS (RX0, TX0, TX1, SPI, HSPI or CLK depending in the pin)
}

uint32_t TSPI1C, TSPI1S, TSPI1U, TSPI1CLK, TSPI1U1;
uint32_t TSPI1C1, TSPI1U2, TSPI1S1, TSPI1P, TSPI1CMD, TSPI1C2;

void saveRegs(){
  TSPI1C=SPI1C, TSPI1U=SPI1U, TSPI1CLK=SPI1CLK, TSPI1U1=SPI1U1, TSPI1U2=SPI1U2;
  TSPI1C1=SPI1C1, TSPI1S1=SPI1S1, TSPI1P=SPI1P, TSPI1CMD=SPI1CMD, TSPI1C2=SPI1C2, TSPI1S=SPI1S;
}

void loadRegs(){
  SPI1C=TSPI1C, SPI1U=TSPI1U, SPI1CLK=TSPI1CLK, SPI1U1=TSPI1U1, SPI1U2=TSPI1U2;
  SPI1C1=TSPI1C1, SPI1S1=TSPI1S1, SPI1P=TSPI1P, SPI1CMD=TSPI1CMD, SPI1C2=TSPI1C2, SPI1S=TSPI1S;
}

void initSPISlave(){
        /*pinMode(MCU_CLK_PIN, SPECIAL);  ///< GPIO14
        pinMode(MCU_MISO_PIN, SPECIAL); ///< GPIO12
        pinMode(MCU_MOSI_PIN, SPECIAL); ///< GPIO13
        pinMode(PIC_CS_PIN, SPECIAL); ///< GPIO15*/
        pinSpecialFast(MCU_CLK_PIN);
        pinSpecialFast(MCU_MISO_PIN);
        pinSpecialFast(MCU_MOSI_PIN);
        pinSpecialFast(PIC_CS_PIN);

    SPI1C = 0;
    SPI1S = SPISE | SPISBE /*| 0x3E0*/;//0x3E0 only for interrupt
    SPI1U = SPIUMISO | SPIUMOSI  | SPIUSSE /*| SPIUDUPLEX*/ ;//sters command
    SPI1CLK = 0;
    SPI1U1 = (512 << SPILMOSI) | (512 << SPILMISO);
    SPI1C1 = 0;//???
    SPI1U2 = (0 << SPILCOMMAND);//no command - does this work?
    
    //SPI1S1 = (((status_len * 8) - 1) << SPIS1LSTA) | (0xff << SPIS1LBUF) | (7 << SPIS1LWBA) | (7 << SPIS1LRBA) | SPIS1RSTA;
    SPI1S1 = (((64 * 8) - 1) << SPIS1LBUF)  ;

    SPI1P = (1 << 19);//poate altu 0 1 2 CS - 1=disable
    SPI1CMD |= SPIBUSY;//START TRF
    //SPI1C2 = (0x1<<SPIC2MISODM_S);  // delays MISO by 1/2 clock cycle. With the help of Günter Ackermann.
    SPI1C2 = (0x2<<SPIC2MOSIDM_S) |(0x7<<SPIC2MOSIDN_S );//SPIC2MOSIDM_S 
  
}

void USB(){
  //receive/send usb packet
  #ifdef DEBUG_TIMING
    pu=!pu;digitalWrite(4,pu);
  #endif
  
  //SPI.begin();//make sure SPI.begin() has been called
  //SPI.beginTransaction(SPISettings(6000000, MSBFIRST, SPI_MODE0));//lower SPI bitrate
  SPI.setClockDivider(0x181001);
  pinMode(PIC_CS_PIN, OUTPUT);
  GPOC = (1<<PIC_CS_PIN); //CS = LOW; select the PIC
  pinMode(MCU_MISO_PIN,SPECIAL); //MISO is SPI-special

  
int nr=0;
  uint8_t rec;

  while(1){
    rec = SPI.transfer(BEGIN_TRANSFER);//send a byte announcing a request
    
    
    if(rec == ACK1){             //response from PIC - ACK1
      #ifdef DEBUG_TRANSACTION
        Serial.print("GOT RESPONSE ");Serial.println(nr);//Serial.println("|");
      #endif
      break;
    } 
    nr++;                         //for timeout functionality
    delayMicroseconds(1);     //wait a bit to allow PIC to finish current action TZEAPA
    if(nr==USB_WAIT_MICROS) {     //timeout
      #ifdef DEBUG_TRANSACTION
        Serial.print(rec);Serial.println("TIMEOUT");
      #endif
      break;}
  }
  if(nr==USB_WAIT_MICROS){
    //we have a timeout
    #ifdef DEBUG_TIMEOUT
      Serial.print(rec,HEX);Serial.println(" TIMEOUT_RESP");
    #endif
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
      
      delayMicroseconds(1);
      cntrusb++;
      /*for(int i=0;i<HAPTIC_IN_BUFFER_SIZE;i++){
        delayMicroseconds(1);
        SPI.transfer(cntrusb/256);//haptic_IN_buffer[i]
      }*/
      uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
      SPI1U1 = ((SPI1U1 & mask) | ((7 << SPILMOSI) | (7 << SPILMISO)));
        
      for(int i=0;i<HAPTIC_IN_BUFFER_SIZE/2;i++){
        
        SPI1W0 = 0x04;
        SPI1CMD |= SPIBUSY;
        while(SPI1CMD & SPIBUSY) {}
        
        SPI1W0 = 0x04;
        SPI1CMD |= SPIBUSY;
        while(SPI1CMD & SPIBUSY) {}
      }
      //same as above but with pointers
      /*for(uint8_t *p=haptic_IN_buffer; p < haptic_IN_buffer+HAPTIC_IN_BUFFER_SIZE; p++){
        delayMicroseconds(1);
        //we can wait 16us total since the packet is 4 times smaller than the others
        SPI.transfer(0x04);//*p
      }*/
    }else if(pkt_requests & REQUEST_OUT){
      //become slave, then receive 49-64 bytes
      GPOS = (1<<PIC_CS_PIN);//PIC will also drive CS HIGH QUICKLY
      saveRegs();
      //we are sure CS is HIGH
      //delayMicroseconds(20);
      initSPISlave();
      //delayMicroseconds(70);
      uint8_t crnr, cnt = GET_TRANSFER_NUMBER;
      //wait for transfer
      do{
        crnr = GET_TRANSFER_NUMBER;
      }while(crnr == cnt);
      //Serial.println(crnr);
      //Serial.println(cnt);
      /*Serial.println(SPI1W0,HEX);
      Serial.println(SPI1W1,HEX);
      Serial.println(SPI1W2,HEX);
      Serial.println(SPI1W3,HEX);
      Serial.println(SPI1W4,HEX);
      Serial.println(SPI1W5,HEX);
      Serial.println(SPI1W6,HEX);
      Serial.println(SPI1W7,HEX);
      Serial.println(SPI1W8,HEX);
      Serial.println(SPI1W9,HEX);
      Serial.println(SPI1W10,HEX);
      Serial.println(SPI1W11,HEX);
      Serial.println(SPI1W12,HEX);
      Serial.println(SPI1W13,HEX);
      Serial.println(SPI1W14,HEX);*/
      //Serial.println(SPI1W15,HEX);
      //Serial.println(micros() - crtm);
      //Serial.println();
      
      //delayMicroseconds(20);
      loadRegs();
      //????????????? VERY WEIRD
      //calling ANY function before and after pinMode
      //(or port manipulation to make pin OUTPUT)
      //seems to speed the USB() call up(A LOT)
      micros();
      //OPTIMIZE THIS
      GPOS = (1<<PIC_CS_PIN); //CS HIGH
      pinMode(PIC_CS_PIN,OUTPUT);
      micros();
      ///now we are master again
      //while we wait for PIC to become slave we can copy the received packet
      if(pkt_requests & REQUEST_DISPLAY_OUT){
        copyPKT(TESTPKT,0);copyPKT(TESTPKT,1);copyPKT(TESTPKT,2);copyPKT(TESTPKT,3);
        copyPKT(TESTPKT,4);copyPKT(TESTPKT,5);copyPKT(TESTPKT,6);copyPKT(TESTPKT,7);
        copyPKT(TESTPKT,8);copyPKT(TESTPKT,9);copyPKT(TESTPKT,10);copyPKT(TESTPKT,11);
        copyPKT(TESTPKT,12);copyPKT(TESTPKT,13);copyPKT(TESTPKT,14);copyPKT(TESTPKT,15); 
      }
      //delayMicroseconds(30);
      //Serial.println(TESTPKT[4],HEX);
      //PIC in now slave
      //we select it once more to send 0x00 to it to "empty" the buffer
      GPOC = (1<<PIC_CS_PIN);
      received=1;
    }
    

      //empty the send/receive buffer
      //delayMicroseconds(1);
      SPI.transfer(0x00);

    
    
  }//end received ACK



  GPOS = (1<<PIC_CS_PIN); //CS = HIGH; deselect the PIC
  
  #ifdef DEBUG_TIMING
    delayMicroseconds(175);
  #endif
}
