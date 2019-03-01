/******************************************************************************/
/******** This file contains SD control modules                     ***********/
/******************************************************************************/
#include "COMMANDS.h"
#include "PSLAB_SD.h"


void SendCommand(BYTE cmd, unsigned long arg) {

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

}


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


