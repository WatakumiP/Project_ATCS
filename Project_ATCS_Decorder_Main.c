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

EE_STATE_V EE_STATE = EE_READ;

void main(void) {
    
    OSCCON =  0x72;
    ANSELA =  0x00;
    
    TRISA =   0x04;
    PORTA =   0x00;
        
    INTCON =  0xC0;
    PIE1 =    0x85;
    PIE2 =    0x10;
    CCP1CON = 0x05;
    T1CON =   0x01;
    
    
    while(1){
        NOP();
    }    
    return;
}