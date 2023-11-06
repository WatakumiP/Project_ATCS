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


void main(void) {
    
    OSCCON = 0x72;
    ANSELA  = 0x00;
    
    TRISA = 0x02;
    PORTA = 0x00;
    
    INTCON = 0xFC;
    OPTION_REG = 0xC0;
    
    while(1){
        
    }    
    return;
}
unsigned int 
void __interrupt() isr(void){
    if(INTCONbits.INTF & ){
        INTCONbits.INTF = 0;
        
    }

}
