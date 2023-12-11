/*
 * Project Auto Train Control System 
 * Ver 0.1
 * 
 * Project Maid by WATANABE
 * Created on 2023/10/27, 12:07
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
#include "Project_ATCS_SETUP.h"

EE_STAGE_DATA EE_STORE __attribute__(()) = {
    EE_NEXT,
    0xFF,
    0x0000,
    {0x0001,0x0FFF,0x0FFF,0x0FFF},
    {0xAA,0x00,0x00,0x00}
};
const UnCHR DCC_ADRS[5] = {
    MuFuD_7bits,
    BaAcD_9bits,
    MuFuD_14bits,
    Reserved_Address,
    AEPF
};                                                                              //データ内部
const UnCHR DCC_DATA[12] = {
    0x00,0x00,0x7F,0x80,0xBF,0xC0,0xE7,0xE8,0xFC,0xFD,0xFE,0xFF
};

UnCHR STACK[32] __at(0xA0);

void main(void) {
    
    OSCCON =  0x72;
    ANSELA =  0x00;
    
    TRISA =   0x04;
    PORTA =   0x00;
    
    INTCON =  0xC0;
    PIE1 =    0x85;
    PIE2 =    0x10;
    CCP1CON = 0x05;
    T1CON =   0x01;
    
    EE_STORE.EE_STATE = EE_WRITE_UID; 
    EEPROM_SELECT();

    
    while(1){
        
        
        if(COM_FLAG & 0x04){
            UnCHR CHECKSUM = 0x00;
            UnCHR PACKET = 0x00;
            UnCHR DCC_PACKET_RANGE = 0x00;
            UnCHR BYPASS[STCR];
            UnCHR DCC_FLAG= 0x00;
            
            DCC_PACKET_RANGE = STCR;            
            COM_FLAG = COM_FLAG & 0xFB;
            while(STCR){
                STCR--;
                BYPASS[STCR];
            }
            
            if(DCC_PACKET_RANGE < 7){
                CHECKSUM = BYPASS[DCC_PACKET_RANGE];
                UnCHR count = 0x00;
                while(DCC_PACKET_RANGE == count){
                    count++;
                    PACKET = PACKET ^ BYPASS[count];
                }
                if(PACKET == BYPASS[DCC_PACKET_RANGE]){
                    if(BYPASS[0] = Broadcast_Address){
                        
                    
                    }
                }
            }
        }
    }
    return;
}