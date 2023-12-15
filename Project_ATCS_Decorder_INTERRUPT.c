/*
 * File:   Project_ATCS_Decorder_INTERRUPT.c
 * Author: WATANABE
 *
 * Created on 2023/12/05, 3:46
 */

#include <xc.h>
#include "Project_ATCS_SETUP.h"
UnCHR COM_FLAG = 0x00;
UnCHR DATA = 0x00;
UnCHR COUNTER = 0x00;
UnCHR STCR = 0x00;

void __interrupt() isr(void){                                                   //非同期動作開始地点
    unsigned short COUNT = 0x00; 

    if(INTCONbits.IOCIF){
        COUNT = TMR1;
        TMR1 = 0x00;
        IOCAF = 0x00;
        
        if(!(COM_FLAG & 0x01)){                                                 //プリアンブル検出
            if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02) ){
                COUNTER++;
            }
            
            else if(COUNT > 0x0080 || COM_FLAG & 0x02){
                if(COUNTER > 11){
                    COM_FLAG = COM_FLAG | 0x01;
                    COM_FLAG = COM_FLAG & 0xFD;
                    COUNTER = 0x00;
                    DATA = 0x00;
                }    
            }
            
        }else if(COM_FLAG & 0x01){                                              //データ受信
            if(COUNTER < 8 ){
                if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02)){
                    DATA = (UnCHR) (DATA << 1) | 0x01;                          
                }else if(COUNT > 0x0080 || COM_FLAG & 0x02){
                    DATA = (UnCHR) (DATA << 1) & 0xFE;
                }
                COUNTER++;
            }
            else{                                                               //エンドビット検出
                if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02)){
                    STACK[STCR] = DATA;
                    COM_FLAG = COM_FLAG | 0x04;
                    COM_FLAG = COM_FLAG & 0xFE;
                }else{
                    if(STCR == 32){
                        STCR = 0;
                    }
                    STACK[STCR] = DATA;
                    COM_FLAG = COM_FLAG & 0xFB;
                    STCR++;
                }
                COUNTER = 0x00;
            }
        }
    }else if(PIR1bits.TMR1IF){
        PIR1 = 0x00;
        COM_FLAG = COM_FLAG | 0x02;
    }else if(PIR2bits.EEIF){
        PIR2bits.EEIF = 0;
        if(EE_STORE.EE_STATE == EE_WRITE_UID){
            EE_STORE.EE_STATE = EE_VERIFY_UID;
        }else if(EE_STORE.EE_STATE == EE_WRITE_ROM){
            EE_STORE.EE_STATE = EE_VERIFY_ROM;            
        }
        EEPROM_SELECT();
    }
}