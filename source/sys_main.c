/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#include "FreeRTOS.h"
#include "os_task.h"
#include "sys_core.h"
#include "sci.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "KaanSat_Lib/microSD.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void rtiNotification(uint32 notification);
void vMicroSD(void *pvParameters);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    gioInit();
    sciInit();
    hetInit();
    // spiInit();  // this happens in the fatfs port

    /* ------------- SR Reader ------------- */
    /** - Initialize LIN/SCI2 Routines to receive Command and transmit data */
    gioToggleBit(gioPORTA, 0U);
    mmcSelectSpi(spiPORT1, spiREG1);        // SD en SPI1
    gioSetBit(gioPORTB, 1, 0);              //Indica escritura
    SD_Test();                              //Inicialización

    gioToggleBit(gioPORTA, 0U);
        sdReadMemory("PRUEBA_6.TXT");
    gioToggleBit(gioPORTA, 0U);
    /* ---------------- Tasks ----------------*/
    xTaskCreate(vMicroSD, "SD", 512, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1);

/* USER CODE END */
}


/* USER CODE BEGIN (4) */
void vMicroSD(void *pvParameters)
{
    int escritura = 0;
    while(1){
        if(!gioGetBit(gioPORTB, 2))
        {
            if(escritura == 0){
                escritura = 1;
            }else{
                escritura = 0;
            }
        }
        UARTprintf("Pase RTI \r\n");
        sprintf(Data_acel, "T: H: A:\r\n");

        if(escritura){
            gioSetBit(gioPORTB, 1, 1);
            sdWriteMemory(TEST_FILENAME, Data_acel);
        }else{
            gioSetBit(gioPORTB, 1, 0);
        }

        vTaskDelay(2000/portTICK_RATE_MS);
    }
}

/* USER CODE END */
