/*
 * Commands.c
 *
 *  Created on: 02/02/2021
 *      Author: Enrique
 */


#include "KaanSat_Lib/Commands.h"
#include "KaanSat_Lib/Utilities.h"
#include "sys_core.h"


char *commands[] = {"CX", "ST", "SIM", "SP1X", "SP2X", "SIMP", "SPR"};
int commandsTam = sizeof (commands)/sizeof (char*);

int sim_ok = 0;
int cmd_cont = 0;
int VALIDA_ENTRADA=0;


void getCommand(char cmd_char)
{

    if(cmd_char != ';')
    {
        CMD_KEY[cmd_cont] = cmd_char;
        cmd_cont++;
    }
    else
    {
        cmd_cont = 0;
        if(CMD_KEY[0] == '+' || CMD_KEY[0] == '-')
        {
            getSPTelemetry(CMD_KEY);
        }
        else
        {
            validate(CMD_KEY);
        }
        memset(CMD_KEY, 0, sizeof(CMD_KEY));                   // Clean the array CMD_KEY to be used again
        memset(receivedData, 0, sizeof(receivedData));
        memset(receivedData2, 0, sizeof(receivedData2));
        memset(receivedData3, 0, sizeof(receivedData3));
        memset(auxReceivedData, 0, sizeof(auxReceivedData));
    }
}

void getSPTelemetry(char *telemetry)
{
    int i;
    int selectSP = -1;
    char *values[] = {"A","B","C","D","E","F"};

    if(telemetry[0] == '+')
        selectSP = 0;
    else
        selectSP = 1;

    char *token = strtok(telemetry,",+-");

    for(i=0; i<6; i++)
    {
        values[i] = token;
        token = strtok(NULL, ",");
    }

    switch(selectSP)
    {
        case 0:
            strcpy(SP1_MISSION_TIME, values[0]);
            strcpy(SP1_PACKET_COUNT, values[1]);
            strcpy(SP1_PACKET_TYPE, values[2]);
            strcpy(SP1_ALTITUDE, values[3]);
            strcpy(SP1_TEMPERATURE, values[4]);
            strcpy(SP1_ROTATION_RATE, values[5]);
            break;
        case 1:
            strcpy(SP2_MISSION_TIME, values[0]);
            strcpy(SP2_PACKET_COUNT, values[1]);
            strcpy(SP2_PACKET_TYPE, values[2]);
            strcpy(SP2_ALTITUDE, values[3]);
            strcpy(SP2_TEMPERATURE, values[4]);
            strcpy(SP2_ROTATION_RATE, values[5]);
            break;
    }
}
void validate(char *comm){

    int validData = 0, commandselect, tokens;
    int noTokens;

    char *commandValue[]={"A"};
    int large=0;

    strcpy(receivedData,comm);
    strcpy(receivedData2,comm);

    strcpy(auxReceivedData,receivedData);
    tokens = numberOfTokens(auxReceivedData,",");
    newData=strtok(receivedData,",");

    if(tokens !=4){validData=1;}

    if(validData == 0){

        validData=strcmp(newData,"CMD");
        if(validData == 0){

            Recorrido(1);
            validData=strcmp(newData,"1714");
            Recorrido(2);
            if(validData == 0){

               commandselect = commVerification(newData,3);
               Recorrido(3);
               commandValue[0]=newData;

                switch (commandselect){
                    case 1:
                    {
                        if((strcmp(newData,"ON") == 0) || (strcmp(newData,"OFF") == 0)){ commCX(&commandValue[0]); }
                        break;
                    }
                    case 2:
                    {
                        strcpy(newDataCopy,newData);
                        noTokens = numberOfTokens(newDataCopy,":");
                        if(noTokens == 3){

                            strcpy(newDataCopy,newData);

                            auxNewData = strtok(newData,":");
                            validData = timeVerification("24",auxNewData,0);//horas

                            if(validData == 0){//minutos
                                RecorridoAuxNewData(1);
                                validData = timeVerification("60",auxNewData,0);

                                if(validData == 0 ){//segundos
                                    RecorridoAuxNewData(2);
                                    validData = timeVerification("60",auxNewData,1);

                                    if(validData == 0){
                                        commST(&commandValue[0]);
                                    }
                                }
                            }
                        }
                        //else{validData = 1;}
                        break;
                    }
                    case 3:
                    {
                        if((strcmp(newData,"ENABLE") == 0) || (strcmp(newData,"DISABLE") == 0) || (strcmp(newData,"ACTIVATE") == 0))
                        { commSIM(&commandValue[0]); }
                    }
                    case 4:
                    {
                        if((strcmp(newData,"ON") == 0) || (strcmp(newData,"OFF") == 0)) { commSP1X(&commandValue[0]); }
                        break;
                    }
                    case 5:
                        {
                            if((strcmp(newData,"ON") == 0) || (strcmp(newData,"OFF") == 0)) { commSP2X(&commandValue[0]); }
                        break;
                    }
                    case 6:
                    {
                        large = strlen(newData);
                        int i=0;
                            for ( i=0; i < strlen(newData)-1; i++)
                            {
                                if((48>newData[i] && 1<=newData[i] ) || (newData[i]>57 && 255>=newData[i])){ validData = 1;}
                                else{validData = 0;}
                            }
                            if( validData == 0){ commSIMP(&commandValue[0]);}

                        break;
                    }
                    case 7:
                    {
                        if((strcmp(newData,"R1") == 0) || (strcmp(newData,"R2") == 0)) { commSPR(&commandValue[0]); }
                        break;
                    }
                    case 12:
                    {
                        break;
                    }
                }
            }
        }
    }
}

int numberOfTokens(char * ptr,const char *delimit){
    char *newToken = strtok(ptr,delimit);
    int count = 0;

    while(newToken != NULL){
        newToken=strtok(NULL,delimit);
        count++;
    }
    return count;
}

int commVerification(char *newData,int x){

    char noWithCero1[]="00,01,02,03,04,05,06,07,08,09";
    char noWithCero2[]="00;,01;,02;,03;,04;,05;,06;,07;,08;,09;";
    char commandsselect[] = "CX,ST,SIM,SP1X,SP2X,SIMP,SPR";
    char *newCaracter;
    int validData, count = 0, found = 1;

    if(x == 0){
        newCaracter = strtok(noWithCero1,",");
    }
    if(x == 1){
        newCaracter = strtok(noWithCero2,",");
    }
    if(x == 3){
        newCaracter = strtok(commandsselect,",");

    }

    while(found!=0 && newCaracter!=NULL){
        validData = strcmp(newData,newCaracter);
        if(validData == 0){
            found = 0;
        }
        newCaracter = strtok(NULL,",");
        count++;
    }

    if(found == 1){
         count = 12;
     }

    return count;
}
void Recorrido(int x){
    int i=0;
    strcpy(receivedData,receivedData2);
    newData = strtok(receivedData,",");
    for( i=0;i<x;i++){
        newData = strtok(NULL,",");
    }
}
int timeVerification(char *x, char *auxNewData, int time){

    int compData=0, validData=0;

    compData = strlen(auxNewData);
    if(compData>2 && time == 0 ){ validData = 1;}
    if(compData>3 && time == 1) {validData = 1;}

    if(validData == 0){
        compData = atoi(auxNewData);

        if(compData <10){//si es menor a 10
            validData = commVerification(auxNewData,time);
            if(validData == 12){validData = 1;}
            else{validData = 0;}
            //printf("menor a 10");
        }
        else{//x=24 o x=60
//            if(time == 1){
//                if(auxNewData[2] != ';'){ validData = 1;}
//            }
            if(validData == 0){
                //  printf("\nHOLA");
                compData = strcmp(auxNewData,x);
                if(compData < 0){ validData = 0; }
                else{validData = 1;}

            }
        }
    }

    return validData;

}
void RecorridoAuxNewData(int x){
    int i=0;
    strcpy(newData,newDataCopy);
    auxNewData = strtok(newData,":");
    for( i=0;i<x;i++){
        auxNewData = strtok(NULL,":");
    }
}

void commCX(char *value[])
{
    //memset(CMD_KEY, 0, sizeof(CMD_KEY));                   // Clean the array CMD_KEY to be used again

    if(!strcmp(*value,"ON"))
    {
        telemetry_ON = true;
    }

    if(!strcmp(*value,"OFF"))
    {
        telemetry_ON = false;
    }
}

void commST(char *value[])
{
    int i;
    char *time[3];
    char *token = strtok(*value,":");

    H =(token[0]-48)*10+(token[1]-48);
    M =(token[3]-48)*10+(token[4]-48);
    S =(token[6]-48)*10+(token[7]-48);

//    for(i=0; i<3; i++)
//    {
//        time[i] = token;
//        token = strtok(NULL, ":;");
//    }
}

void commSIM(char *value[])
{
    if(sim_ok == 0 && (!strcmp(*value,"ENABLE")))
    {
        sim_ok = 1;
    }
    else if(sim_ok == 1 && (!strcmp(*value,"DISABLE")))
    {
        sim_ok = 0;
    }
    else if(sim_ok == 1 && (!strcmp(*value,"ACTIVATE")))
    {
        sim_ok = 1;
    }

}
void commSP1X(char *value[])
{
    if(!strcmp(*value,"ON"))
    {
        SP1X_ON = true;
    }
    if(!strcmp(*value,"OFF"))
    {
        SP1X_ON = false;
    }
}
void commSP2X(char *value[])
{
    if(!strcmp(*value,"ON"))
    {
        SP2X_ON = true;
    }
    if(!strcmp(*value,"OFF"))
    {
        SP2X_ON = false;
    }
}

void commSIMP(char *value[])
{
    PRESS_BAR = atof(*value);
}

void commSPR(char *value[]){

    int angles[3] = {SPOS_ZERO, SPOS_SP1, SPOS_SP2};

    if(!strcmp(*value,"R1"))
    {
        R1 = true;
        SERVO_PAYLOAD.duty = angles[1];
    }

    if(!strcmp(*value,"R2"))
    {
        R2 = true;
        SERVO_PAYLOAD.duty = angles[2];
    }
}
