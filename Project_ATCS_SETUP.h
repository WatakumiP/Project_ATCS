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

typedef enum EE_SR{
    EE_READ = 0,
    EE_WRITE_UID,
    EE_VERIFY_UID,
    EE_WRITE_ROM,
    EE_VERIFY_ROM,
    EE_NEXT
}EE_STATE_V;

typedef unsigned int UnINT;
typedef unsigned char UnCHR;

// COMフラグについては、別途記載のドキュメント参照のこと。
extern UnCHR COM_FLAG;
extern UnCHR DATA;
extern UnCHR EE_FLAG;
extern UnINT COUNTER;
extern EE_STATE_V EE_STATE;

UnCHR DATA_Sampling(void);
void Preamble(void);

#endif	


