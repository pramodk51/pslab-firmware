/******************************************************************************/
/******** This file contains SD control modules                     ***********/
/******************************************************************************/
#include "COMMANDS.h"
#include "PSLAB_SD.h"



/**************Helper Functions******************/

inline void SDSelectLow(void){
    //make the select line low using GPIO
    //will implement this later after discussing
}

inline void SDSelectHigh(void){
   //make the select line high using GPIO
}




inline BYTE SDReadResp(void){ 
    
    //continuously sends the dummy byte 0xFF to the SD card,
    //until the response back is not busy
    BYTE v, i = 0;      
     do{                 
          v = spi_write8(0xFF); 
     }while(i++ < 128 && (v == 0xFF));      
     return v; 
     
} 


/****************APIs for external world****************/
//for this CRC function see below link
//http://nerdclub-uk.blogspot.com/2012/11/how-spi-works-with-sd-card.html

BYTE SDCRC(BYTE* chr,BYTE cnt,BYTE crc){ 
     BYTE i, a; 
     BYTE Data; 

     for(a = 0; a < cnt; a++){           
          Data = chr[a];           
          for(i = 0; i < 8; i++){                
               crc <<= 1; 
               if( (Data & 0x80) ^ (crc & 0x80) ) {crc ^= 0x09;}                
               Data <<= 1; 
          } 
     }      
     return crc & 0x7F; 
} 



BYTE SDSendCommand(BYTE cmd, unsigned long arg) {

    BYTE res;
    
    SDSelectHigh();
    //write a dummy byte can ignored also
    spi_write8(0xFF);
    SDSelectLow(); 
    //spi_write8(0xFF);
    
    
     BYTE send_arr[6]; 
     send_arr[0] = cmd | 0x40; 
     send_arr[1] = arg >> 24; 
     send_arr[2] = arg >> 16; 
     send_arr[3] = arg >> 8; 
     send_arr[4] = arg; 
     send_arr[5] = (SDCRC(send_arr, 5, 0) << 1) | 1; 
      
     for(cmd = 0; cmd < sizeof(send_arr); cmd++){ 
          spi_write8(send_arr[cmd]); 
     } 
     
     //get the response
     res=SDReadResp();
     
     return res;
}
/*
//SD Result structure to be defined
SDResult SD_Init(SDCardType *x){


    // Initialize SPI for use with the memory card
    initSPI();        //change accordingly
    SDSelectHigh();
    //low frequency for initialization
    //lowClockSPI();     //will implement it later
        
        
    //for initialization 
    //We must supply at least 74 clocks with CS high
    BYTE i;
    for(i = 0; i < 12; i++) { 
          spi_write8(0xFF);     //lots of clocks to give card time to init 
     } 

    ////////////////
    ///////////////
    
    
    
}

*/



