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
UnCHR COM_FLAG = 0x00;
UnCHR DATA = 0x00;
UnINT COUNTER = 0x00; 

void main(void) {
    
    OSCCON =  0x72;
    ANSELA =  0x00;
    
    TRISA =   0x04;
    PORTA =   0x00;
    
    INTCON =  0xC0;
    PIE1 =    0x85;
    CCP1CON = 0x05;
    T1CON =   0x01;
    
    
    while(1){
        NOP();
    }    
    return;
}

void __interrupt() isr(void){
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
    }
}