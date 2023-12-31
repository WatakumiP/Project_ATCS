/*
 Name:		Project_ATCS_CONTROLER.ino
 Created:	2023/12/20 19:25:15
*/

#include <Wire.h>
#include "DCC_CORE.h"
#include "AGTimerR4.h"

void setup() {
    Wire.begin();
    Wire.onRequest(I2C_RECIVED);
    Serial.begin(9600);
}

void loop() {
    static UnCHR Count = 0x00;
    if (Count == 0xff) {
        Count = 0x00;
    }
    Wire.beginTransmission(1);
    Wire.write(Count);
    Count++;
}

void I2C_RECIVED() {
    char sxc = Wire.read();
    Serial.print(sxc);
}