// 
// 
// 

#include "DCC_CORE.h"
#define DCC_HI D9				//IN1 
#define DCC_LOW D10			//IN2
#define DelayT_H 46			//1
#define DelayT_F 100			//0
#define DCC_bitREAD(value,bit) (((value) >> (bit)) & 0x01) ? DelayT_H : DelayT_F 

DCC_SEND_MODULE::DCC_SEND_MODULE(){
	pinMode(DCC_HI, OUTPUT);
	pinMode(DCC_LOW, OUTPUT);
}

void DCC_SEND_MODULE::DCC_SEND_DIR(UnCHR ADRS,UnCHR DT) {
	ADDRESS = ADRS;
	DATA = DT;
	CHKSUM = ADRS ^ DT;
	Serial.print("MODULEADDRESS : ");
	Serial.println(ADDRESS,HEX);
	Serial.print("MODULEDATA : ");
	Serial.println(DATA, HEX);
	Serial.print("MODULECHKSUM : ");
	Serial.println(CHKSUM, HEX);
	for (UnCHR i = 0; i < 2; i++)
	{
		SEND_PREAMBLE();
		SEND_ADDRESS();
		SEND_DATA();
		SEND_CHKSUM();
	}
}
void DCC_SEND_MODULE::SEND_PREAMBLE(void) {
	UnSHT count = 0;
	while (count < 16) {
		digitalWrite(DCC_HI, HIGH);
		digitalWrite(DCC_LOW, LOW);
		delayMicroseconds(DelayT_H);
		digitalWrite(DCC_HI, LOW);
		digitalWrite(DCC_LOW, HIGH);
		delayMicroseconds(DelayT_H);
		count++;
	}
	digitalWrite(DCC_HI, HIGH);
	digitalWrite(DCC_LOW, LOW);
	delayMicroseconds(DelayT_F);
	digitalWrite(DCC_HI, LOW);
	digitalWrite(DCC_LOW, HIGH);
	delayMicroseconds(DelayT_F);
	return;
}
void DCC_SEND_MODULE::SEND_ADDRESS() {
	UnCHR count = 7;
	do{
		digitalWrite(DCC_HI, HIGH);
		digitalWrite(DCC_LOW, LOW);
		delayMicroseconds(DCC_bitREAD(ADDRESS, count));
		digitalWrite(DCC_HI, LOW);
		digitalWrite(DCC_LOW, HIGH);
		delayMicroseconds(DCC_bitREAD(ADDRESS, count));
		count--;
	} while (count);
	digitalWrite(DCC_HI, HIGH);
	digitalWrite(DCC_LOW, LOW);
	delayMicroseconds(DelayT_F);
	digitalWrite(DCC_HI, LOW);
	digitalWrite(DCC_LOW, HIGH);
	delayMicroseconds(DelayT_F);
}

void DCC_SEND_MODULE::SEND_DATA() {
	UnCHR count = 7;
	do{
		digitalWrite(DCC_HI, HIGH);
		digitalWrite(DCC_LOW, LOW);
		delayMicroseconds(DCC_bitREAD(DATA, count));
		digitalWrite(DCC_HI,	LOW);
		digitalWrite(DCC_LOW, HIGH);
		delayMicroseconds(DCC_bitREAD(DATA, count));
		count--;
	} while (count);
	digitalWrite(DCC_HI, HIGH);
	digitalWrite(DCC_LOW, LOW);
	delayMicroseconds(DelayT_F);
	digitalWrite(DCC_HI, LOW);
	digitalWrite(DCC_LOW, HIGH);
	delayMicroseconds(DelayT_F);
}

void DCC_SEND_MODULE::SEND_CHKSUM() {
	UnCHR count = 7;
	do{
		digitalWrite(DCC_HI, HIGH);
		digitalWrite(DCC_LOW, LOW);
		delayMicroseconds(DCC_bitREAD(CHKSUM, count));
		digitalWrite(DCC_HI, LOW);
		digitalWrite(DCC_LOW, HIGH);
		delayMicroseconds(DCC_bitREAD(CHKSUM, count));
		count--;
	} while (count);
	digitalWrite(DCC_HI, HIGH);
	digitalWrite(DCC_LOW, LOW);
	delayMicroseconds(DelayT_H);
	digitalWrite(DCC_HI, LOW);
	digitalWrite(DCC_LOW, HIGH);
	delayMicroseconds(DelayT_H);
	digitalWrite(DCC_HI, LOW);
	digitalWrite(DCC_LOW, LOW);
}

