/*
 * microSD.h
 *
 *  Created on: 20/04/2021
 *      Author: Enrique
 */

#ifndef INCLUDE_KAANSAT_LIB_MICROSD_H_
#define INCLUDE_KAANSAT_LIB_MICROSD_H_

#include "sci.h"
#include "stdio.h"
#include "gio.h"
#include "spi.h"
#include "uartstdio.h"
#include "het.h"
#include "math.h"

#define TEST_FILENAME    "PRUEBA_8.TXT"

FIL filew; //file txt
FRESULT iFResult;

char Data_acel[100];
int res;

int sdWriteMemory(char* path, char* data);

#endif /* INCLUDE_KAANSAT_LIB_MICROSD_H_ */