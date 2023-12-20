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
void (*PKT_FUNC[])(void) = {
    DEC_SET,
    DEC_SET,
    SPD_SET,
    SPD_SET,
    FUNC_SET,           //
    FUNC_SET,           //ファンクション命令 F5-
    FT_EXPANSION,       //BiDiなのはわかってるけどこの子に入れられないのでNULL
    CONFIG_SET
};

UnCHR STACK[32] __at(0xA0);
UnCHR SPEED[2];
UnCHR PACKET_FLAG;

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
    
    CCP1CON =  0x0F;
    PSTR1CON = 0x01;
    PR2 =      0x19;
    CCPR1L =   0x3F;
    T2CON =    0x04;
    
    EE_STORE.EE_STATE = EE_WRITE_UID; 
    EEPROM_SELECT();
    while(1){
        if(COM_FLAG & 0x04){
            COM_FLAG &= 0xFB;
            UnCHR CKS = STACK[0];
            
            if(STCR < 7){
                for(UnCHR count = 1 ;count < STCR;count++){
                    CKS = CKS ^ STACK[STCR];
                }
                
                if(CKS == STACK[STCR]){
                    UnCHR PACK = STACK[1] >> 5;
                    if(STACK[0] == Broadcast_Address){
                        PKT_FUNC[PACK]();
                    }else if(STACK[0] <= MuFuD_7bits){
                        EE_STORE.EE_ADRS = 0x00;
                        EE_STORE.EE_STATE = EE_READ_S;
                        EE_STORE.EE_CONFIG = EUID_CON;
                        EE_STORE.EE_REPORT[0] = 0xAA;
                        EEPROM_SELECT();
                        if(STACK[0] == EE_STORE.EE_DATA[0]){
                            PKT_FUNC[PACK]();
                        }
                    }
                }       
            }
        }
    }
    return;
}