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

extern void SendCommand(BYTE cmd, unsigned long arg);
extern BYTE SDCRC(BYTE* chr,BYTE cnt,BYTE crc);






#ifdef	__cplusplus
}
#endif

#endif	/* PSLAB_SD_H */

