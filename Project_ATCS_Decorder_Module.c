/*
 * File:   Project_ATCS_Decorder_SinkLayer.c
 * Author: WATANABE
 * ver 0.1
 * Created on November 22, 2023, 11:35 PM
 */


#include <xc.h>
#include "Project_ATCS_SETUP.h"

void EEPROM_SELECT(void) {
    INTCONbits.GIE = 0;                                                         //割り込み禁止
    UnCHR COUNT = 0x00 ;
    
    switch (EE_STORE.EE_STATE) {                                                //EE_STATEより
        case EE_READ_S:                                                         //読み込みシングルモード
            do{
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EECON1 = EE_STORE.EE_CONFIG;
                    while (EECON1bits.RD);
                    EE_STORE.EE_DATA[COUNT] = EEDAT;
                    INTCONbits.GIE = 1;
                    EE_STORE.EE_REPORT[COUNT] = 0x00;
                    return;
                }
                COUNT++;
                EEADR = EE_STORE.EE_ADRS++;
            }while(COUNT < 4);
            return;

        case EE_READ_M:                                                         //読み込みマルチ 
            do {
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EECON1 = EE_STORE.EE_CONFIG;
                    EECON1bits.RD = 1;
                    while (EECON1bits.RD);
                    EE_STORE.EE_DATA[COUNT] = EEDAT;
                    EE_STORE.EE_REPORT[COUNT] = 0x00;
                }
                EE_STORE.EE_ADRS++;
            } while (COUNT < 4);
            INTCONbits.GIE = 1;
            return;

        case EE_WRITE_UID:                                                      //ユーザーID書き込み
            INTCONbits.GIE = 0;                                                 //シーケンス開始
            UnINT EE_SAVE = EE_STORE.EE_ADRS;
            do {
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EEDAT = EE_STORE.EE_DATA[COUNT];
                    EECON1 = 0x64;
                    EECON2 = 0x55;
                    EECON2 = 0xAA;
                    EECON1bits.WR = 1;
                }
                COUNT++;
                EE_STORE.EE_ADRS++;
            } while (COUNT < 4);
            EE_STORE.EE_ADRS = EE_SAVE;
            
            EECON1 = 0x44;
            EECON2 = 0x55;
            EECON2 = 0xAA;

            EECON1bits.WR = 1;
            NOP();
            NOP();
            INTCONbits.GIE = 1;
            return;                                                             //メインに戻す

        case EE_VERIFY_UID:                                                     //ユーザー書込成否チェック
            INTCONbits.GIE = 0;
            do {
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EECON1 = 0x41;
                    while (EECON1bits.RD);
                    if (EEDAT != EE_STORE.EE_DATA[COUNT]) {
                        EE_STORE.EE_REPORT[COUNT] = 0xFF;
                    } else {
                        EE_STORE.EE_REPORT[COUNT] = 0x00;
                    }
                }
                COUNT++;
                EE_STORE.EE_ADRS++;
            } while (COUNT < 4);
            INTCONbits.GIE = 1;
            return;

        case EE_WRITE_ROM:                                                      //データEEPROM書き込み
            do{
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EEDAT = EE_STORE.EE_DATA[COUNT];
                    EECON1 = 0x44;
                    EECON2 = 0x55;
                    EECON2 = 0xAA;
                    EECON1bits.WR = 1;
                    NOP();
                    NOP();
                    INTCONbits.GIE = 1;
                    return;
                }
                COUNT++;
                EEADR = EE_STORE.EE_ADRS++;
            }while(COUNT < 4);
            INTCONbits.GIE = 1;
            return;
            
        case EE_VERIFY_ROM:                                                     //データEEPROM書込成否チェック
            do{
                if(EE_STORE.EE_REPORT[COUNT]){
                    EEADR = EE_STORE.EE_ADRS;
                    EECON1 = 0x01;
                    while (EECON1bits.RD);
                    EE_STORE.EE_DATA[COUNT] = EEDAT;
                    if (EEDAT != EE_STORE.EE_DATA[COUNT]) {
                        EE_STORE.EE_REPORT[COUNT] = 0xFF;
                    } else {
                        EE_STORE.EE_REPORT[COUNT] = 0x00;
                    }
                    return;
                }
                COUNT++;
                EEADR = EE_STORE.EE_ADRS++;
            }while(COUNT < 4);
            INTCONbits.GIE = 1;
            return;

        default:                                                                //それ以外はチェック無しで返す。
            return;
    }
}
void PACKET_CONTROL(UnCHR *DATA, UnCHR *P_RANGE){
    switch(DATA[1] >> 5){
        case 0:
            COM_FLAG &= 0xF7;
            DEC_SET(DATA,P_RANGE);
            return;
        case 1:
            COM_FLAG |= 0x08;
            DEC_SET(DATA,P_RANGE);
            return;
        case 2:
            COM_FLAG |= 0x10;
            PWM_SET(DATA,P_RANGE);
            return;
        case 3:
            COM_FLAG &= 0xEF;
            PWM_SET(DATA,P_RANGE);
            return;
        case 4:
            COM_FLAG &= 0xDF;
            FUNC_SET(DATA,P_RANGE);
            return;
        case 5:
            COM_FLAG |= 0x20;
            FUNC_SET(DATA,P_RANGE);
            return;
        case 6:
            NOP();
            return;
        case 7:
            CONFIG_SET(DATA,P_RANGE);
            return;
    }
}
void DEC_SET(UnCHR *DATA,UnCHR *P_RANGE){
    
    
}
void PWM_SET(UnCHR *DATA,UnCHR *P_RANGE){}
void FUNC_SET(UnCHR *DATA,UnCHR *P_RANGE){}
void CONFIG_SET(UnCHR *DATA,UnCHR *P_RANGE){}