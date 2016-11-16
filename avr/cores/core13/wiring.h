/*
 * Core13 wiring library
 *
 * Based of the original core13 v0.22 by John "smeezekitty",
 * distributed under the LGPL v2+.
 * 
 * This is a derivative work under the LGPL license © 2016 Daniel Lima <danielm@tinyhub.tk>
 */
#ifndef Wiring_h
#define Wiring_h

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

class _wiring {
public:
	static void out(uint8_t pin) {
		DDRB |= _BV(pin);
	}
	static void in(uint8_t pin) {
		DDRB &= ~_BV(pin);
	}
	static void hi(uint8_t pin) {
		PORTB |= _BV(pin);
	}
	static void lo(uint8_t pin) {
		PORTB &= ~_BV(pin);
	}
};
extern _wiring _w;

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define false 0
#define FALSE 0
#define TRUE 1
#define true 1
#define PI 3.1416
#define HALF_PI 1.57
#define TWO_PI 6.283
#define DEG_TO_RAD 0.0174533
#define RAD_TO_DEG 57.2958
#define SERIAL 0
#define DISPLAY 1
#define LSBFIRST 0
#define MSBFIRST 1
#define CHANGE 1
#define FALLING 2
#define RISING 3
#define INTERNAL 1
#define EXTERNAL 0
#define DEFAULT 0
#ifdef abs
#undef abs
#endif
#define abs(x) ((x)>0?(x):-(x))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
#define interrupts() sei()
#define noInterrupts() cli()
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define microsecondsToClockCycles(a) ( ((a) * (F_CPU / 1000L)) / 1000L )
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
typedef unsigned int word;
#define bit(b) (1UL << (b))
typedef uint8_t boolean;
typedef uint8_t byte;
void init(void);

// void pinMode(uint8_t, uint8_t);
#define pinMode(pin, mode)\
do {\
	if (mode == OUTPUT) _w.out(pin);\
	else {\
		_w.in(pin);\
		if (mode == INPUT_PULLUP) _w.hi(pin);\
	}\
} while(0)

// void digitalWrite(uint8_t, uint8_t);
#define digitalWrite(pin, value) do { if (value == HIGH) _w.hi(pin); else _w.lo(pin); } while(0)
#define digitalToggle(pin) do { PINB |= bit(pin); } while (0)
uint8_t digitalRead(uint8_t);
int analogRead(uint8_t); 
void analogReference(uint8_t mode);
void analogWrite(uint8_t, uint8_t);
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned ms);
void delayMicroseconds(int us);
void shiftOut(uint8_t, uint8_t, uint8_t, uint8_t);
uint8_t shiftIn(uint8_t, uint8_t, uint8_t);
unsigned long pulseIn(unsigned char pin, unsigned char stat, unsigned long timeout);
//void attachInterrupt(uint8_t, void (*)(void), int mode);
//void detachInterrupt(uint8_t);
void setup(void);
void loop(void);

#endif//Wiring_h
