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
    



    //TO DO OUT VECTOR
#define REP8(x) x x x x x x x x

#define strgf(x) str_H(x)
#define str_H(X) #X
#define MOVLW_ADR(X) asm(strgf(M_CONC(MOVLW 0x, X)));


#define _XTAL_FREQ 48000000
void spiRead(void){
    if(BF){
        TESTB=SSPBUF;
        REGT=0x22;
        if(TESTB == 0x55){
            //service transfer
            SSPBUF = 0x76;
            while(WCOL){    //write the SYNC RECEIVED CODE(0x76)
                WCOL=0;
                SSPBUF = 0x76;
            }
            while(!BF);
            
            SSPBUF = 0x00;
            while(WCOL){    //write the SYNC RECEIVED CODE(0x76)
                WCOL=0;
                SSPBUF = 0x00;
            }
            while(!BF);
            REGT=0x11;
        }
        
        //SSPBUF=0xff-TESTB;
        //REGT=SSPCON1;
        WCOL=0;
        SSPOV=0;
        
    }
}

char v[8]="ABCDEFGH";

void spwrh(){
    /*
     
     * 
     * 
     * MOVLW 0xD0
0B9E  0086     MOVWF FSR1L
0B9F  3021     MOVLW 0x21
0BA0  0087     MOVWF FSR1H
0BA1  3141     ADDFSR 1, 1--------------
0BA2  0801     MOVF INDF1, W
0BA3  0091     MOVWF SSP1BUF
0BA4  1C14     BTFSS SSP1STAT, 0x0
0BA5  2BA7     GOTO 0x3A7
0BA6  2BA8     GOTO 0x3A8
0BA7  2BA4     GOTO 0x3A4
     */
    ////TESTING RECEIVE ON DISPLAY AND SEND ON HAPTIC
    //preload address
    //address for DISPLAY
    MOVLW_ADR(DISPLAY_DATA_ADDRESS_LO)     //asm("MOVLW 0xD0");
    asm("MOVWF FSR1L");
    MOVLW_ADR(DISPLAY_DATA_ADDRESS_HI)     //asm("MOVLW 0x21");
    asm("MOVWF FSR1H");
    
    //address for HAPTIC_IN
    /*asm("MOVLW 0x30");
    asm("MOVWF FSR0L");
    asm("MOVLW 0x22");
    asm("MOVWF FSR0H");*/
    
    
    //go to bank 4, where the spbuf/stat is
    asm("MOVLB 4");
    
    REP8(REP8(writeByteNOread))
    
     
    /*SSPBUF = display_output[0];while(!BF);//7f=DEL
    SSPBUF = display_output[1];while(!BF);//7f=DEL
    SSPBUF = display_output[2];while(!BF);//7f=DEL
    SSPBUF = display_output[3];while(!BF);//7f=DEL
    SSPBUF = display_output[4];while(!BF);//7f=DEL
    SSPBUF = display_output[5];while(!BF);//7f=DEL
    SSPBUF = display_output[6];while(!BF);//7f=
    SSPBUF = display_output[7];while(!BF);//7f=DEL*/
    
}
int cnt_tr=0;

void spiWrite(){
    if(cnt_tr<1000){ 
       cnt_tr++;
        return;
    }
    cnt_tr=0;
    CS_PIN = 0;
    //__delay_us(100);
    
    spwrh();
    //spwrh("ASDFQWER");
    //spwrh("POIUYTRE");
    //spwrh("PLMNJKOI");
    //spwrh("GHBNVFTY");
    //spwrh("12398754");
    //spwrh(",./;'[]-");
    //spwrh("GHtjhv/]");
    //spwrh("-=6`4f;z");
    
    SSPBUF = ' ';while(!BF);
    CS_PIN = 1;
}

void MasterinitSPI(){
    TRIS_CS_PIN = 0;TRIS_CLK_PIN = 0;
  
#if SPI_FREQ == 6
    SSPADD = 1;
#endif
    SSPSTAT = SAMPLE_MIDDLE |  ACTIVE_TO_IDLE;//SMP=0;CKE=1
    SSPCON = SPI_MODE | IDLE_LOW;//SSPM=0000:=;CKP=0
    
}
void SlaveinitSPI(){
    TRIS_CS_PIN = 1;TRIS_CLK_PIN = 1;
    //BOEN = 0;
    //ANSC0=0;ANSC1=0;ANSC2=0;ANSC3=0; moved to system.c
    
    SSPSTAT = SAMPLE_MIDDLE |  ACTIVE_TO_IDLE;//SMP=0;CKE=1
    SSPCON = SLAVE_SS_EN | IDLE_LOW;//SSPM=0000:=;CKP=0
}