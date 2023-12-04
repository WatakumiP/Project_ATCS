/*
 * File:   Project_ATCS_Decorder_SinkLayer.c
 * Author: WATANABE
 * ver 0.1
 * Created on November 22, 2023, 11:35 PM
 */


#include <xc.h>
#include "Project_ATCS_SETUP.h"

void EEPROM_SLCT(){
    switch(EE_STATE){
        case EE_READ:               //読み込み開始（アドレスは各自指定）
            EEADRL = 0x00;
            EEADRH = 0x00;
            INTCONbits.GIE = 0;
            EECON1 = 0x41; // RDをセット
            while(EECON1bits.RD);
            if(EEDATL != 0x00){
                
            }
            return;
            
        case EE_WRITE_UID:          //ユーザーID書き込み
            INTCONbits.GIE = 0;     //シーケンス開始
            EECON1 = 0x44;      
            EECON2 = 0x55;
            EECON2 = 0xAA;
            EECON1bits.WR = 1;  
            return;                  //メインに戻す
  
        case EE_VERIFY_UID:          //ユーザー書込成否チェック
            EEADRL = 0x00;
            EEADRH = 0x00;
            INTCONbits.GIE = 0;
            EECON1 = 0x41; // RDをセット
            while(EECON1bits.RD);
            if(EEDATL != 0x00){
            }
            return;
        
        case EE_WRITE_ROM:           //データEEPROM書き込み
            INTCONbits.GIE = 0;     //シーケンス開始
            EECON1 = 0x44;      
            EECON2 = 0x55;
            EECON2 = 0xAA;
            EECON1bits.WR = 1;  
            return;
            
        case EE_VERIFY_ROM:          //データEEPROM書込成否チェック
            EEADRL = 0x00;
            EEADRH = 0x00;
            INTCONbits.GIE = 0;
            EECON1 = 0x01; // RDをセット
            while(EECON1bits.RD);
            if(EEDATL != 0x00){
            }
            return;
            
        default:                     //それ以外はチェック無しで返す。
            return;
        
    }
}