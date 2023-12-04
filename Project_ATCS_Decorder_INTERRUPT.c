/*
 * File:   Project_ATCS_Decorder_INTERRUPT.c
 * Author: owata
 *
 * Created on 2023/12/05, 3:46
 */


#include <xc.h>
#include "Project_ATCS_SETUP.h"
UnCHR COM_FLAG = 0x00;
UnCHR DATA = 0x00;
UnINT COUNTER = 0x00; 

void __interrupt() isr(void){                                                   //非同期動作開始地点
    int COUNT = 0x00;
    if(PIR1bits.CCP1IF){
        PIR1  = 0x00;
        TMR1H = 0x00;
        TMR1L = 0x00;
        COUNT = CCPR1H << 8 | CCPR1L;
        if(!(COM_FLAG & 0x01)){                                                 //プリアンブル検出
            if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02) ){
                COUNTER++;
            }
            else if(COUNT > 0x0080 || COM_FLAG & 0x02){
                if(COUNTER > 11){
                    COM_FLAG = COM_FLAG | 0x01;
                    COM_FLAG = COM_FLAG & 0xFD;
                    COUNTER = 0x00;
                }    
            }
        }else if(COM_FLAG & 0x01){                                              //データ受信
            if(COUNTER < 8 ){
                if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02) ){
                    DATA = (UnCHR) (DATA << 1) | 0x01;                          
                }else if(COUNT > 0x0080 || COM_FLAG & 0x02){
                    DATA = (UnCHR) (DATA << 1) & 0xFE;
                }
                COUNTER++;
            }
            else{                                                               //エンドビット検出
                if(COUNT >= 0x00C0 && COUNT <= 0x0100 && !(COM_FLAG & 0x02)){
                    COM_FLAG = COM_FLAG | 0x04;
                    COM_FLAG = COM_FLAG & 0xFE;
                }else{
                    COM_FLAG = COM_FLAG & 0xFB;
                }
                COUNTER = 0x00;
            }
        }
    }else if(PIR1bits.TMR1IF){
        PIR1 = 0x00;
        COM_FLAG = COM_FLAG | 0x02;
    }else if(PIR2bits.EEIF){
        if(EE_STATE == EE_WRITE_UID){
            EE_STATE = EE_VERIFY_UID;
        }else if(EE_STATE == EE_WRITE_ROM){
            EE_STATE = EE_VERIFY_ROM;
        }else{
            EE_STATE = EE_NEXT;
        }
    }
}