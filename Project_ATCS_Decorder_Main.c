/*
 * Project Auto Train Control System 
 * Ver 1.0
 * 
 * Project Maid by WATANABE
 * Created on 2023/10/27, 12:07
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
#include "Project_ATCS_SETUP.h"
UnCHR COM_FLAG = 0x00;



void main(void) {
    
    OSCCON = 0x72;
    ANSELA  = 0x00;
    
    TRISA = 0x02;
    PORTA = 0x00;
    
    INTCON = 0xD0;
    OPTION_REG = 0x40;
    
    while(1){
        
    }    
    return;
}

void __interrupt() isr(void){
    static UnCHR READ = 0x00;
    if(INTCONbits.INTF && (COM_FLAG & 0x01) == 0 ){
        INTCONbits.INTF = 0;
        READ++; 
        if(READ == 0x0F){
            COM_FLAG = 0x01;
            READ = 0x00;
        }
    }
    else if(INTCONbits.INTF && (COM_FLAG & 0x01) == 0 ){
        INTCONbits.INTF = 0;
        COM_FLAG = 0x00; 
        RA4 = ~RA4;
    }
}
