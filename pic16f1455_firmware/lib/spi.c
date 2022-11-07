#include <xc.h>
#include "include/spi.h"

#include "include/app_device_joystick.h"

#define SPI_FREQ 6
#if SPI_FREQ == 6
    #define SPI_MODE MASTER_OSC_SPADD
#else
    #define SPI_MODE MASTER_OSC_DIV4
#endif

#define writeByteNOread asm("MOVIW FSR1++");/*load next byte*/   \
    asm("MOVWF SSP1BUF");                      /*output to SPI*/    \
    asm("BTFSS SSP1STAT, 0x0");            /*if ready continue*/    \
    asm("BRA -2");                         /*else go back*/         \
    asm("MOVF SSP1BUF,W");                /*read the received byte into W*/
    
#define writeByteRead asm("MOVIW FSR1++");/*load next byte*/   \
    asm("MOVWF SSP1BUF");                      /*output to SPI*/    \
    asm("BTFSS SSP1STAT, 0x0");            /*if ready continue*/    \
    asm("BRA -2");                         /*else go back*/         \
    asm("MOVF SSP1BUF,W");                /*read the received byte into W*/ \
    asm("MOVWI FSR0++");/*save received byte*/
    
#if SPI_FREQ == 6
    #define WAIT_ADDITIONAL NOP();NOP();NOP();NOP();  NOP();NOP();NOP();NOP(); 
#else
    #define WIAT_ADDITIONAL
#endif



#define writeByteNOreadFAST asm("MOVIW FSR1++");/*load next byte*/  \
    asm("MOVWF SSP1BUF");                      /*output to SPI*/    \
    NOP();NOP();NOP();NOP();   NOP();NOP();NOP();NOP();NOP();   \
    WAIT_ADDITIONAL                                                 \
    asm("MOVF SSP1BUF,W");                /*read the received byte into W*/
    
#define writeByteReadFAST asm("MOVIW FSR1++");/*load next byte*/  \
    asm("MOVWF SSP1BUF");                      /*output to SPI*/    \
    NOP();NOP();NOP();NOP();   NOP();NOP();NOP();NOP();NOP();   \
    WAIT_ADDITIONAL                                                 \
    asm("MOVF SSP1BUF,W");                /*read the received byte into W*/ \
    asm("MOVWI FSR0++");/*save received byte*/
    

#define writeByteOnlyRead asm("BTFSS SSP1STAT, 0x0"); /*if ready continue*/   \
                asm("BRA -2");              /*else go back*/                  \
                asm("MOVF SSP1BUF,W");      /*read the received byte into W*/ \
                asm("MOVWI FSR0++");        /*save received byte*/  

    //TO DO OUT VECTOR
#define REP8(x) x x x x x x x x

#define strgf(x) str_H(x)
#define str_H(X) #X
#define MOVLW_ADR(X) asm(strgf(M_CONC(MOVLW 0x, X)));


#define _XTAL_FREQ 48000000



uint8_t garbage;

uint8_t luminosity;//first control byte to receive
uint8_t errors_ctr2_to_PIC;//second control byte to send

uint8_t pkt_requests;//bitmask for each packet type
uint8_t ctrl2_from_PIC;//second ctrl byte

void spiWrite(void);

void spiTask(void){
    pkt_requests = 0;
    if(!HIDTxHandleBusy(last_HAP_IN)){
        //rady to send another to PC
        pkt_requests = REQUEST_HAPTIC_IN;
    }
    if(!HIDRxHandleBusy(last_DSP_OUT)){
        //rady to send another to PC
        pkt_requests = REQUEST_DISPLAY_OUT;
    }
    //in case we have received a start command 
    //from previous unserviced transaction
    garbage = SSPBUF;
    SSPOV = 0;
    //wait for a new byte, only for 3 microseconds
    
        asm("MOVLB 4");
    REP8(asm("BTFSC SSP1STAT, 0x0"); asm("BRA OUTOFWAITSPI");)
    REP8(asm("BTFSC SSP1STAT, 0x0"); asm("BRA OUTOFWAITSPI");)
    asm("OUTOFWAITSPI: NOP");                
    
    ///we have waited for a "fresh" request
    if(BF && SSPBUF == BEGIN_TRANSFER){
        //if we have a request(we have received BEGIN_TRANSFER)
        //service transfer
        SSPBUF = ACK1;
        //in case we write exactly during a receive the WCOL will be set
        
        while(!BF);//wait for response
        if(SSPBUF == BEGIN_TRANSFER){
            //we haven't just missed the NodeMCU's interval
            //it sends 0x00 to indicate it timed out
            //else it sends another BEGIN_TRANSFER to read the ACK1
            SSPBUF = pkt_requests;
            //we surely don't have overflow; NodeMCU waits 1us
            asm("BTFSS SSP1STAT, 0x0");            //if ready continue
            asm("BRA -2");                         //else go back
            
            luminosity = SSPBUF;
            
            SSPBUF = ctrl2_from_PIC;
            //we surely don't have overflow; NodeMCU waits 1us
            asm("BTFSS SSP1STAT, 0x0");            //if ready continue
            asm("BRA -2");                         //else go back
            
            errors_ctr2_to_PIC = SSPBUF;
            //we have transmitted and received control bytes
            
            if(pkt_requests & REQUEST_HAPTIC_IN){
                hap_IN_pkt_sent=0;
                
                
                //read 16 bytes
                MOVLW_ADR(HAPTIC_IN_ADDRESS_LO)
                asm("MOVWF FSR0L");
                MOVLW_ADR(HAPTIC_IN_ADDRESS_HI)
                asm("MOVWF FSR0H");
                asm("MOVLB 4");//go to bank 4, where the spbuf/stat is
                
                asm("MOVF SSP1BUF,W");
                REP8(writeByteOnlyRead)
                REP8(writeByteOnlyRead)
                        
                //asm("BTFSS SSP1STAT, 0x0"); //if ready continue   
                //asm("BRA -2");              //else go back             
                //asm("MOVF SSP1BUF,W");      //read the received byte into W
                SSPBUF = 0x00;
            }else if(pkt_requests & REQUEST_DISPLAY_OUT){
                display_pkt_ready = 1;
                //__delay_us(10);
                MasterinitSPI();
                __delay_us(5);
                spiWrite();
                __delay_us(3);//NodeMCU has to copy the packet
                SlaveinitSPI();
                //__delay_us(3);
                SSPBUF = 0x00;
                while(!BF);
                return;
            }
            
        }else{
            //we don't need to send another 0x00
            //since BUF is already 0(or at least not BEGIN_TRANSFERs)
            return;
        }
            
        
    }
    //make sure no ACK1 byte is left in BUF
    SSPBUF = 0x00;
    WCOL=0;
    SSPOV=0;
}

void spiWrite(){
    CS_PIN = 0;
    //preload address
    //address for DISPLAY
    MOVLW_ADR(DISPLAY_DATA_ADDRESS_LO)     //asm("MOVLW 0xD0");
    asm("MOVWF FSR1L");
    MOVLW_ADR(DISPLAY_DATA_ADDRESS_HI)     //asm("MOVLW 0x21");
    asm("MOVWF FSR1H");
    
    //go to bank 4, where the spbuf/stat is
    asm("MOVLB 4");
    
    REP8(REP8(writeByteNOread))
    //NodeMCU needs to receive one more dummy byte
    SSPBUF = ' ';while(!BF);
    
    CS_PIN = 1;
}

void MasterinitSPI(){
    CS_PIN=1;
    TRIS_CS_PIN = 0;TRIS_CLK_PIN = 0;
  
#if SPI_FREQ == 6
    SSPADD = 1;
#endif
    SSPSTAT = SAMPLE_MIDDLE |  IDLE_TO_ACTIVE;//SMP=0;CKE=1
    SSPCON = SPI_MODE | IDLE_LOW;//SSPM=0000:=;CKP=0
    
}
void SlaveinitSPI(){
    TRIS_CS_PIN = 1;TRIS_CLK_PIN = 1;
    //BOEN = 0;
    //ANSC0=0;ANSC1=0;ANSC2=0;ANSC3=0; moved to system.c
    
    SSPSTAT = SAMPLE_MIDDLE |  ACTIVE_TO_IDLE;//SMP=0;CKE=1
    SSPCON = SLAVE_SS_EN | IDLE_LOW;//SSPM=0000:=;CKP=0
}