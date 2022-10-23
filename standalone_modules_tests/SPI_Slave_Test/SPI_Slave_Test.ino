/*void SPIClass::begin() {
    

    --SPI1C = 0;
    --setFrequency(1000000); ///< 1MHz
    --SPI1U = SPIUMOSI | SPIUDUPLEX | SPIUSSE;
    --SPI1U1 = (7 << SPILMOSI) | (7 << SPILMISO);
    SPI1C1 = 0;
}*/

#define SCK  14
#define MISO 12
#define MOSI 13
#define CS   15

uint8_t cnt;

uint32_t vec_send[16]={0x00000000,0x11111111,0x22222222,0x33333333,0x44444444,0x55555555,0x66666666,0x77777777,
      0x88888888,0x99999999,0xaaaaaaaa,0xbbbbbbbb,0xcccccccc,0xdddddddd,0xeeeeeeee,0xffffffff,};

void initSPI(){
        pinMode(SCK, SPECIAL);  ///< GPIO14
        pinMode(MISO, SPECIAL); ///< GPIO12
        pinMode(MOSI, SPECIAL); ///< GPIO13
        pinMode(CS, SPECIAL); ///< GPIO15

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
    SPI1C2 = (0x2<<SPIC2MOSIDM_S) /*(0x3<<SPIC2MOSIDN_S )*/;//SPIC2MOSIDM_S 
  
}

void setup() {
  Serial.begin(500000);
  //Serial.setDebugOutput(true);
  initSPI();
 
  cnt = ((ESP8266_REG(0x100+4*12))>>23)&0xf;
}


#define regname(x) SPI1W##x
//#define prreg(x) Serial.print((char)regname(x) );Serial.print((char)(regname(x) >>8));Serial.print((char)(regname(x) >>16));Serial.print((char)(regname(x) >>24));
#define prreg(x) Serial.print((char)regname(x),HEX );Serial.print((char)(regname(x) >>8),HEX);Serial.print(' ');Serial.print((char)(regname(x) >>16),HEX);Serial.print((char)(regname(x) >>24),HEX);Serial.print(' ');
//#define pr8reg(x) prreg(x) prreg(x+1) prreg(x+2) prreg(x+3) prreg(x+4) prreg(x+5) prreg(x+6) prreg(x+7)

uint8_t crnr;
void loop() { 
  do{
    crnr = (((ESP8266_REG(0x100+4*12))>>23)&0xf);
  }while(crnr == cnt);
  cnt=crnr;
  //Serial.println(SPI1CMD   ,HEX);
  /*for(int i=0;i<32;i++)   
    {Serial.print(ESP8266_REG(0x100+4*i),HEX);Serial.print(" ");} */
    Serial.print(cnt);Serial.print('\t');
//while((GPI & (1<<15)) !=0 ){}
//while((GPI & (1<<15)) ==0 ){}
  delayMicroseconds(50);
  //Serial.print("Hello ");
  //Serial.print((SPI1CMD & SPIBUSY)!=0);//Serial.print(" ");

prreg(0)
prreg(1)
prreg(2)
prreg(3)
prreg(4)
prreg(5)
prreg(6)
prreg(7)
prreg(8)
prreg(9)
prreg(10)
prreg(11)
prreg(12)
prreg(13)
prreg(14)
prreg(15)


SPI1W0=vec_send[0];
SPI1W1=vec_send[1];
SPI1W2=vec_send[2];
SPI1W3=vec_send[3];
SPI1W4=vec_send[4];
SPI1W5=vec_send[5];
SPI1W6=vec_send[6];
SPI1W7=vec_send[7];
SPI1W8=vec_send[8];
SPI1W9=vec_send[9];
SPI1W10=vec_send[10];
SPI1W11=vec_send[11];
SPI1W12=vec_send[12];
SPI1W13=vec_send[13];
SPI1W14=vec_send[14];
SPI1W15=vec_send[15];



Serial.println();
//delay(100);
}
