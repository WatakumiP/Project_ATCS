/*
 * File:   Project_ATCS_Decorder_SinkLayer.c
 * Author: WATANABE
 * ver 0.1
 * Created on November 22, 2023, 11:35 PM
 */


#include <xc.h>
#include "Project_ATCS_SETUP.h"

void Preamble(){
    UnCHR CO = 0x00;
    while(COM_FLAG & 0x01){
        COM_FLAG = COM_FLAG & 0xFB;
        while(COM_FLAG & 0x04);
        CO++;
    } 
    if(CO >= 12){
        COM_FLAG = COM_FLAG & 0xF7;
    }
} 
UnCHR DATA_Sampling(){
    UnCHR CO = 0x00;
    while(CO < 8){
        if(COM_FLAG & 0b00000100){
            if(COM_FLAG & 0b00000001){
                DATA = (UnCHR) (DATA << 1) | 0x01;
            }else{
                DATA = (UnCHR) (DATA << 1) & 0xFE;
            }
            COM_FLAG = COM_FLAG & 0xFB;
            CO++;
        }
    }
    while((COM_FLAG & 0x04) == 0);
    if(COM_FLAG & 0b00000001){
        COM_FLAG = COM_FLAG & 0xFB;
        return 0;
    }else{
        COM_FLAG = COM_FLAG & 0xFB;
        return 1;
    }
}