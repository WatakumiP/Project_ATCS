#ifndef SETUP_H
#define	SETUP_H

#include<xc.h>

#pragma config FOSC = INTOSC    // Oscillator Selection 
#pragma config WDTE = OFF       // Watchdog Timer Enable 
#pragma config PWRTE = ON       // Power-up Timer Enable 
#pragma config MCLRE = OFF      // MCLR Pin Function Select 
#pragma config CP = OFF         // Flash Program Memory Code Protection 
#pragma config CPD = OFF        // Data Memory Code Protection 
#pragma config BOREN = ON       // Brown-out Reset Enable 
#pragma config CLKOUTEN = OFF   // Clock Out Enable 
#pragma config IESO = OFF       // Internal/External Switchover 
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable 

#pragma config WRT = OFF        // Flash Memory Self-Write Protection 
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable 
#pragma config BORV = HI        // Brown-out Reset Voltage Selection  
#pragma config LVP = OFF        // Low-Voltage Programming 

#define Broadcast_Address 0x00
#define MuFuD_7bits 0x7F
#define BaAcD_9bits 0xBF
#define MuFuD_14bits 0xE7
#define Reserved_Address 0xFC
#define AEPF 0xFE
#define IDLE 0xFF



typedef enum EE_SR{
    EE_READ_S = 0,
    EE_READ_M,
    EE_WRITE_UID,
    EE_VERIFY_UID,
    EE_WRITE_ROM,
    EE_VERIFY_ROM,
    EE_NEXT
}EE_SR;

typedef unsigned int UnINT;
typedef unsigned char UnCHR;

// COMフラグについては、別途記載のドキュメント参照のこと。
extern UnCHR COM_FLAG;
extern UnCHR DATA;
extern UnCHR EE_FLAG;
extern UnCHR COUNTER;
extern UnCHR STACK[32];

typedef struct EE_STAGE_DATA{
    EE_SR EE_STATE;               //状態を指す、EE_SRで指定する
    UnCHR EE_CONFIG;           //コンフィグ、EECON1の中身
    UnINT EE_ADRS;                //アドレス、中身は14bitで。
    UnINT EE_DATA[4];             //データ、中身は15bitで抑えて。
    UnCHR EE_REPORT[4];           //レポート記述 0x00 = DONE; 0xAA = READY;  0xFF = ERROR;
} EE_STAGE_DATA;

extern EE_STAGE_DATA EE_STORE;

UnCHR DATA_Sampling(void);
void Preamble(void);
void EEPROM_SELECT(void);


#endif	


