/*********************************************************************
 * Railuino - Hacking your Märklin
 *
 * Copyright (C) 2012 Joerg Pleumann
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LICENSE file for more details.
 */
 
#include "TrackReporterS88_DS.h"

// ===================================================================
// === TrackReporterS88_DS ==============================================
// ===================================================================

const uint8_t DATA = A0;
const uint8_t CLOCK = D12;
const uint8_t S_nL = D11;
const uint8_t RESET = D5;
const uint8_t TIME = 25;

TrackReporterS88_DS::TrackReporterS88_DS(int modules) 
{
	mSize = modules;
	
	pinMode(DATA, INPUT);
	digitalWrite(DATA, LOW);// Pullup disabled
	
	pinMode(CLOCK, OUTPUT);
	pinMode(S_nL, OUTPUT);
	pinMode(RESET, OUTPUT);
	digitalWrite(S_nL, LOW);
}

void TrackReporterS88_DS::refresh()
{
	refresh(mSize);
}

void TrackReporterS88_DS::refresh(int inMaxSize)
{
	int myByte = 0;
	int myBit = 0;
	int aCntMax = inMaxSize << 4;

	for (int i = 0; i < sizeof(mSwitches); i++) 
	{
		mSwitches[i] = 0;
	}

	// データ取得開始
	digitalWrite(S_nL, HIGH);

	for (int i = 0; i < aCntMax; i++) 
	{
		digitalWrite(CLOCK, HIGH);
		delayMicroseconds(TIME);
		digitalWrite(CLOCK, LOW);
		bitWrite(mSwitches[myByte], myBit++, digitalRead(DATA));

		if (myBit == 8) {
			myByte++;
			myBit = 0;
		}

		delayMicroseconds(TIME);
	}
	digitalWrite(S_nL, LOW);
}

boolean TrackReporterS88_DS::getValue(int index) {
	index--;
	return bitRead(mSwitches[index / 8], index % 8);
}

byte TrackReporterS88_DS::getByte(int index) {
	return mSwitches[index];
}
