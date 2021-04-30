/*
 * Commands.h
 *
 *  Created on: 02/02/2021
 *      Author: Enrique
 */

#ifndef INCLUDE_KAANSAT_LIB_COMMANDS_H_
#define INCLUDE_KAANSAT_LIB_COMMANDS_H_

extern char *commands[];
extern int commandsTam;


enum
{
    CX,ST,SIM,SP1X,SP2X,SIMP,SPR
};

extern int sim_ok;


static char receivedData[22];
static char receivedData2[22];
static char receivedData3[22];
static char auxReceivedData[22];
char *newData;

char newDataCopy[10];//copia de new data
//char *time_hms[10];
char  *auxNewData;// auxNewData recorre en newData para el tiempo en el caso 2


void getSPTelemetry(char *telemetry);
void getCommand(char cmd_char);
int findCommand(char *comm);
void commCX();
void commST(char *value[]);
void commSIM(char *value[]);
void commSP1X(char *value[]);
void commSP2X(char *value[]);
void commSIMP(char *value[]);
void commSPR(char *value[]);

void validate(char *comm);
int numberOfTokens(char *,const char *delimit);
int commVerification(char *,int x);
void Recorrido(int x);

int timeVerification(char *x, char *newData, int time);//TIEMPO
void RecorridoAuxNewData(int x);//TIEMPO




#endif /* INCLUDE_KAANSAT_LIB_COMMANDS_H_ */
