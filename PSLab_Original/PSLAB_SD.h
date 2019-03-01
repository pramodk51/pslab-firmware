/* 
 * File:   PSLAB_SD.h
 * Author: user
 *
 * Created on February 12, 2019, 1:07 PM
 */

#ifndef PSLAB_SD_H
#define	PSLAB_SD_H

#include "PSLAB_SPI.h"

#ifdef	__cplusplus
extern "C" {
#endif


/*Definitions of SD commands */
#define CMD0    (0x40+0)        /* GO_IDLE_STATE            */
#define CMD1    (0x40+1)        /* SEND_OP_COND (MMC)       */
#define ACMD41  (0xC0+41)       /* SEND_OP_COND (SDC)       */
#define CMD8    (0x40+8)        /* SEND_IF_COND             */
#define CMD9    (0x40+9)        /* SEND_CSD                 */
#define CMD10   (0x40+10)       /* SEND CID                 */
#define CMD16   (0x40+16)       /* SET_BLOCKLEN             */
#define CMD17   (0x40+17)       /* READ_SINGLE_BLOCK        */
#define CMD24   (0x40+24)       /* WRITE_SINGLE_BLOCK       */
#define CMD42   (0x40+42)       /* LOCK_UNLOCK              */
#define CMD55   (0x40+55)       /* APP_CMD                  */
#define CMD58   (0x40+58)       /* READ_OCR                 */
#define CMD59   (0x40+59)       /* CRC_ON_OFF               */
    
    
    
#define SD_INIT_TRYS    0x03

/* CardType */
#define SDCT_MMC        0x01                    /* MMC version 3    */
#define SDCT_SD1        0x02                    /* SD version 1     */
#define SDCT_SD2        0x04                    /* SD version 2     */
#define SDCT_SDC        (SDCT_SD1|SDCT_SD2)     /* SD               */
#define SDCT_BLOCK      0x08                    /* Block addressing */

#define SD_BLK_SIZE     512
    
    
    
typedef struct {
     
    BYTE     Type;             // Card type (detected by SD_Init())
    BYTE     CSD[16];          // SD card CSD register (card structure data)
    BYTE     CID[16];          // SD card CID register (card identification number)
    BYTE     SCR1[8];          // SD card SCR register (SD card configuration)   
    unsigned long LAST_SECTOR; //last sector in sd card
} SDCardType;
    
    
/* Results of SD functions */
typedef enum {
    SD_OK =   0,       /* 0: Function succeeded    */
    SD_NOINIT=1,       /* 1: SD not initialized    */
    SD_ERROR= 2,       /* 2: Disk error            */
    SD_PARERR=3,       /* 3: Invalid parameter     */
    SD_BUSY=  4,       /* 4: Programming busy      */
    SD_REJECT=5,       /* 5: Reject data           */
    SD_NORESPONSE=6    /* 6: No response           */
} SDResult;    



    
extern BYTE SDSendCommand(BYTE cmd, unsigned long arg);
extern BYTE SDCRC(BYTE* chr,BYTE cnt,BYTE crc);
//extern SDResult SD_Init(SDCardType *x);





#ifdef	__cplusplus
}
#endif

#endif	/* PSLAB_SD_H */

