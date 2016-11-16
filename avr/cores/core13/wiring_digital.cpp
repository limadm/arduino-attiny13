/*
 * Core13 wiring_digital library
 *
 * Based of the original core13 v0.22 by John "smeezekitty",
 * distributed under the LGPL v2+.
 * 
 * This is a derivative work under the LGPL license © 2016 Daniel Lima <danielm@tinyhub.tk>
 */
#include "wiring_private.h"

#ifndef pinMode
void pinMode(uint8_t pin, uint8_t mode) {
	if (mode == OUTPUT) {
		DDRB |= _BV(pin);
	} else {
		DDRB &= ~_BV(pin);
		if (mode == INPUT_PULLUP) {
			PORTB |= _BV(pin);
		}
	}
}
#endif
#ifndef turnOffPWM
void turnOffPWM(uint8_t timer){
	if(timer == 0){
		TCCR0A &= ~_BV(COM0A1);
	}
	if(timer == 1){
		TCCR0A &= ~_BV(COM0B1);
	}
}
#endif
#ifndef digitalWrite
void digitalWrite(uint8_t pin, uint8_t val){
	if(!val){
		PORTB &= ~_BV(pin);
	} else {
		PORTB |= _BV(pin);
	}
}
#endif
#ifndef digitalRead
uint8_t digitalRead(uint8_t pin){
	return !!(PINB & _BV(pin));
}
#endif
