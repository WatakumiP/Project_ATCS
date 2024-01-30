/*
 Name:		Project_ATCS_CONTROLER.ino
 Created:	2023/12/20 19:25:15
*/

#include "DCC_CORE.h"

#define DebugMODE

#ifdef DebugMODE	// 全体デバッグモード
#define I2CDebug
#define S88Debug
#define DCCDebug
#endif 

#define VDD_S A1
#define TRAIN_COUNT 3

LiquidCrystal_I2C lcd(LCD_UNIT, 16, 2);
TrackReporterS88_DS S88N(1);
DCC_SEND_MODULE DCC_TEST;

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Project  ATCS ");
    lcd.setCursor(0, 1);
    lcd.print("Check USB Port");
    Serial.begin(115200);
    while (!Serial);             // Leonardo: wait for serial monitor
    pinMode(VDD_S,INPUT);
#ifdef I2CDebug
    Serial.println("\nActivate DebugMode");
    byte ccounter = 0x00;
    // --------------------------------------
    // i2c_scanner
    //
    // Version 1
    //    This program (or code that looks like it)
    //    can be found in many places.
    //    For example on the Arduino.cc forum.
    //    The original author is not know.
    // Version 2, Juni 2012, Using Arduino 1.0.1
    //     Adapted to be as simple as possible by Arduino.cc user Krodal
    // Version 3, Feb 26  2013
    //    V3 by louarnold
    // Version 4, March 3, 2013, Using Arduino 1.0.3
    //    by Arduino.cc user Krodal.
    //    Changes by louarnold removed.
    //    Scanning addresses changed from 0...127 to 1...119,
    //    according to the i2c scanner by Nick Gammon
    //    http://www.gammon.com.au/forum/?id=10896
    // Version 5, March 28, 2013
    //    As version 4, but address scans now to 127.
    //    A sensor seems to use address 120.
    // Version 6, November 27, 2015.
    //    Added waiting for the Leonardo serial communication.
    //
    //
    // This sketch tests the standard 7-bit addresses
    // Devices with higher bit address might not be seen properly.
    //
    byte error = 0, address = 0;
    int nDevices;
    Serial.println("\nI2C Scanner");
    Serial.println("Scanning...");

    nDevices = 0;
    for (byte count = 1; count < 127; count++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.print("\n");
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            Serial.print("\n");
        }
        address++;
    }

    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
#endif 
    byte MATEST;
    UnCHR ERC = 0;
    do{
        unsigned short MAcount = 3;
        do {
            int cckl = 0;
            Wire.beginTransmission(MA_CTRL);
            Wire.write(0xFF);
            Wire.endTransmission();
            delay(5000);
            Wire.requestFrom(MA_CTRL, 1);
            while (Wire.available()) {
                MATEST = Wire.read();
#ifdef I2CDebug
                Serial.println(MATEST, HEX);
                Serial.println(Wire.available());
#endif
            }
            if (MATEST == 0xAA) {
                break;
            }
            MAcount--;
        } while (MAcount);
        if (MATEST != 0xAA) {
            if (!ERC) {
                Serial.println("Master Controler");
                Serial.println("Connection ERROR");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Master Controler");
                lcd.setCursor(0, 1);
                lcd.print("Connection ERROR");
            }
            delay(2000);
            continue;
        }
        else {
            Serial.println("Master Controler");
            Serial.println("Connection OK");
            break;
        }
    }while (1);
    ERC = 0;
    
    while (analogRead(A1) < 400) {
        if (!ERC) {
            Serial.println("Power Connection ERROR");
            Serial.println("Check DC cable");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("POWER CONNECTOR");
            lcd.setCursor(0, 1);
            lcd.print("Connection ERROR");
            ERC++;
        }
    }
    Serial.println("Power Connection OK");

    attachInterrupt(digitalPinToInterrupt(D3),OVR_CUR_ISR, RISING);
    delay(1000);
    lcd.clear();
    lcd.print("Project ATCS");
    lcd.setCursor(0, 1);
    lcd.print("READY");
}

void loop() {
    static  DCC_SPDC SPD[4] = { {0x01,0x7F,0} ,{0x02,0x60,1},{0x03,0x60,2} ,{0x7F,0x60,0} };
    UnCHR Counter = 0;
    UnCHR Reporter;
    S88N.refresh();
#ifdef S88Debug
    while (Counter < 1) {
        Reporter = S88N.getByte(Counter);
        Counter++;
        Serial.print("Now read Address :");
        Serial.println(Reporter, HEX);
    }
#endif 
    Counter = 0;
    if (S88N.getValue(3))                                                   //加速部分
    {
        
    }
    else if (S88N.getValue(4)) {                                        //減速部分
        UnCHR SPCON = 0;
        UnCHR SPCT = 0;
        while (SPD[Counter].DCC_STOP) {
            Counter++;
            Serial.println("4_++");
        }
        while (SPD[Counter].DCC_DATA != 0x73) {
            UnCHR SWAP;
            SPCON = SPD[Counter].DCC_DATA & 0x1F;
            if (!(SPCT % 10)) {
                if (SPCON & 0x10) {
                    SPCON &= 0xEF;
                }
                else {
                    SPCON |= 0x10;
                    SPCON--;
                }
            }
            SPCT++;
            SPD[Counter].DCC_DATA = SPD[Counter].DCC_DATA & 0xE0;
            SPD[Counter].DCC_DATA = SPD[Counter].DCC_DATA | SPCON;
            DCC_TEST.DCC_SEND_DIR(SPD[Counter].DCC_ADDRESS, SPD[Counter].DCC_DATA);
            Serial.println(Counter, HEX);
            Serial.println(SPD[Counter].DCC_ADDRESS, HEX);
            Serial.println(SPD[Counter].DCC_DATA, HEX);
        }
        UnCHR SELC = 0;
        while (SELC < TRAIN_COUNT) {
            if (SPD[SELC].DCC_STOP)
            {
                SPD[SELC].DCC_STOP--;
            }
            else {
                SPD[SELC].DCC_STOP = 2;
            }
            SELC++;
            Serial.println("4_--");
        }
        while (1) {                                                                                             //入線処理
            if (!(S88N.getValue(1)) && !(S88N.getValue(2))) {                                  //どちらも空いている場合（そんな状況はない気がします。）
                DCC_TEST.DCC_SEND_DIR(0x7F, 0x00);
                while (S88N.getValue(1)) {
                    S88N.refresh();
                    DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
                }
                DCC_TEST.DCC_SEND_DIR(SPD[Counter].DCC_ADDRESS, 0x60);
                break;
            }
            else if (!(S88N.getValue(1)) && S88N.getValue(2)) {                             //1番が空いている場合
                DCC_TEST.DCC_SEND_DIR(0x7F, 0x00);
                while (!(S88N.getValue(1))) {
                    S88N.refresh();
                    DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
                }
                DCC_TEST.DCC_SEND_DIR(SPD[Counter].DCC_ADDRESS, 0x60);
                break;
            }
            else if (S88N.getValue(1) && !(S88N.getValue(2))) {                             //2番が空いている場合・
                DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
                while (!(S88N.getValue(2))) {
                    S88N.refresh();
                    DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
                }
                DCC_TEST.DCC_SEND_DIR(SPD[Counter].DCC_ADDRESS, 0x60);
                break;
            }
            else if (S88N.getValue(1) && S88N.getValue(2)) {                                //両方空いていない場合(発進処理)
                UnCHR CounterSWAP = 0;
                while (SPD[CounterSWAP].DCC_STOP) {
                    CounterSWAP++;
                }
                DCC_TEST.DCC_SEND_DIR(SPD[CounterSWAP].DCC_ADDRESS, 0x73);
                S88N.refresh();
                while (!(S88N.getValue(1)) && !(S88N.getValue(1))) {
                    S88N.refresh();
                    DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
                }
            }
        }
    }
    else {
        DCC_TEST.DCC_SEND_DIR(0xFF, 0x00);
    }
}
void OVR_CUR_ISR() {
    digitalWrite(D9, HIGH);
    digitalWrite(D10, HIGH);
    lcd.clear();
    lcd.print("CURRENT PROTECT");
    lcd.setCursor(0, 1);
    lcd.print("ENABLE");
    Serial.println("Current Protection Enable");
    Serial.println("Please ALL DCC_DECORDER Dismount");
}