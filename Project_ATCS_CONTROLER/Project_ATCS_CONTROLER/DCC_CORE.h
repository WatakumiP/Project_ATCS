#ifndef DCC_CORE_H
#define DCC_CORE_H

#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include "TrackReporterS88_DS.h"

typedef unsigned char UnCHR ;
typedef unsigned short UnSHT;
typedef unsigned long UnLNG ;

#define MA_CTRL 0x1f
#define LCD_UNIT 0x27


class DCC_SEND_MODULE {

public:
	DCC_SEND_MODULE();

	void DCC_SEND_DIR(UnCHR ADRS,UnCHR DT);
private:
	void SEND_PREAMBLE(void);
	void SEND_ADDRESS();
	void SEND_DATA();
	void SEND_CHKSUM();
	UnCHR ADDRESS;
	UnCHR DATA;
	UnCHR CHKSUM;
};
struct DCC_SPDC
{
	UnCHR DCC_ADDRESS;
	UnCHR DCC_DATA;
	UnSHT DCC_STOP;
};
#endif // !DCC_CORE_H
