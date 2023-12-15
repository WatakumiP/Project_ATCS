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
    {0x0055,0x0FFF,0x0FFF,0x0FFF},
    {0xAA,0x00,0x00,0x00}
};
const UnCHR DCC_ADRS[5] = {
    MuFuD_7bits,
    BaAcD_9bits,
    MuFuD_14bits,
    Reserved_Address,
    AEPF
};                                                                              //データ内部
const UnCHR PWM_DATA[64] = {
    0x00,0x00,0x7F,0x80,0xBF,0xC0,0xE7,0xE8,0xFC,0xFD,0xFE,0xFF
};
UnCHR STACK[32] __at(0xA0);

void main(void) {
    
    OSCCON =  0x72;
    ANSELA =  0x00;
    
    TRISA =   0x04;
    PORTA =   0x00;
    
    APFCON =  0x03;
    
    INTCON =  0xC8;
    IOCAP =   0x04;
    PIE1 =    0x81;
    PIE2 =    0x10;
    T1CON =   0x01;
    
    CCP1CON = 0x0F;
    PSTR1CON = 0x01;
    PR2 =     0x19;
    CCPR1L =  0x3F;
    T2CON =   0x04;
    
    EE_STORE.EE_STATE = EE_WRITE_UID; 
    EEPROM_SELECT();
    
    while(1){
        
        if(COM_FLAG & 0x04){
            UnCHR CHECKSUM = 0x00;
            UnCHR DCC_PACKET_RANGE = STCR;
            UnCHR BYPASS[32];
            UnCHR PACKET = STACK[0];
                        
            COM_FLAG = COM_FLAG & 0xFB;
            do{
                STCR--;
                BYPASS[STCR] = STACK[STCR];
            }while(STCR);
            
            if(DCC_PACKET_RANGE < 7){
                CHECKSUM = STACK[DCC_PACKET_RANGE];
                for(UnCHR count = 1 ;count < DCC_PACKET_RANGE;count++){
                    PACKET = PACKET ^ BYPASS[count];
                }
                
                if(PACKET == STACK[DCC_PACKET_RANGE]){
                    if(BYPASS[0] == Broadcast_Address){
                        PACKET_CONTROL(BYPASS,&DCC_PACKET_RANGE);
                    }else if(BYPASS[0] <= MuFuD_7bits){
                        EE_STORE.EE_ADRS = 0x00;
                        EE_STORE.EE_STATE = EE_READ_S;
                        EE_STORE.EE_CONFIG = EUID_CON;
                        EE_STORE.EE_REPORT[0] = 0xAA;
                        EEPROM_SELECT();
                        if(BYPASS[0] == EE_STORE.EE_DATA[0]){
                            PACKET_CONTROL(BYPASS,&DCC_PACKET_RANGE);
                        }
                    }
                }       
            }
        }
    }
    return;
}