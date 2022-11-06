#ifndef SPI_H
#define	SPI_H

#define TRIS_CS_PIN TRISC3
#define TRIS_MISO_SDO_PIN TRISC2
#define TRIS_MOSI_SDI_PIN TRISC1
#define TRIS_CLK_PIN TRISC0

#define CS_PIN PORTCbits.RC3

#define BEGIN_TRANSFER 0x55
#define ACK1 0x76


//OUT_type 2 bits, IS_OUT 1 bit, IS_IN1 bit
#define REQUEST_HAPTIC_IN   0x01  //0001
#define REQUEST_OUT         0x02  //0010
#define REQUEST_HAPTIC_OUT  0x06  //0110
#define REQUEST_LED_OUT     0x0A  //1010
#define REQUEST_DISPLAY_OUT 0x0E  //1110

#include <xc.h> // include processor files - each processor file is guarded.  
 
uint8_t TESTB,REGT;

extern uint8_t luminosity;//first control byte to receive
extern uint8_t errors_ctr2_to_PIC;//second control byte to send

extern uint8_t pkt_requests;//bitmask for each packet type
extern uint8_t ctrl2_from_PIC;//second ctrl byte

typedef enum
{
  MASTER_OSC_DIV4  = 0b00100000,
  MASTER_OSC_DIV16 = 0b00100001,
  MASTER_OSC_DIV64 = 0b00100010,
  MASTER_TMR2_DIV2 = 0b00100011,
  MASTER_OSC_SPADD = 0b00101010,
          
  SLAVE_SS_EN      = 0b00100100,
  SLAVE_SS_DIS     = 0b00100101
}Spi_Mode;
 
typedef enum
{
  SAMPLE_MIDDLE = 0b00000000,
  SAMPLE_END    = 0b10000000
}Spi_Data_Sample;
 
typedef enum
{
  IDLE_HIGH = 0b00001000,
  IDLE_LOW  = 0b00000000
}Spi_Clock_Pol;
 
typedef enum
{
  IDLE_TO_ACTIVE = 0b00000000,
  ACTIVE_TO_IDLE = 0b01000000
}Spi_Clock_Edge;
 
/*void spiWrite2(char dat){
    SSPBUF = dat;
}*/
 
//void spiRead(void);
void spiTask(void);

void MasterinitSPI(void);
void SlaveinitSPI(void);


#endif	/* SPI_H */

