/*
*** Core13 ***
Arduino core designed for Attiny13 and similar devices.
NO WARRANTEE OR GUARANTEES!
Written by John "smeezekitty" 
You are free to use, redistribute and modify at will EXCEPT IF MARKED OTHERWISE IN A PARTICULAR SOURCE FILE!
Version 0.22
*/
#include "wiring_private.h"

uint8_t shiftIn(uint8_t d, uint8_t c, uint8_t ord) {
	uint8_t value = 0;
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		digitalWrite(c, HIGH);
	/*	if(ord == LSBFIRST){value |= digitalRead(d) << i;}
		else{value |= digitalRead(d) << (7 - i);}*/
		value |= (digitalRead(d) << ((ord == LSBFIRST)?i:7-i));
		digitalWrite(c, LOW);
	}
	return value;
}

void shiftOut(uint8_t d, uint8_t c, uint8_t ord, uint8_t val)
{
	uint8_t i;
	for (i = 0; i < 8; i++)  {
		if(ord == LSBFIRST){digitalWrite(d, !!(val & (1 << i)));}
		else{digitalWrite(d, !!(val & (1 << (7 - i))));}
		digitalWrite(c, HIGH);
		asm("nop");
		digitalWrite(c, LOW);		
	}
}
