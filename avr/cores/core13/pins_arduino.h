/*
 * Core13 pin definitions for the ATtiny13 microcontroller
 *
 *                  +--_--+
 * Ain0 (D 5) PB5  1|     |8  Vcc
 * Ain3 (D 3) PB3  2|     |7  PB2 (D 2) Ain1
 * Ain2 (D 4) PB4  3|     |6  PB1 (D 1) PWM
 *            GND  4|     |5  PB0 (D 0) PWM
 *                  +-----+
 *
 * Based of the original core13 v0.22 by John "smeezekitty",
 * distributed under the LGPL v2+.
 * 
 * This is a derivative work under the LGPL license © 2016 Daniel Lima <danielm@tinyhub.tk>
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

// ATtiny have just the B port.
#define digitalPinToPort(P) (PORTB)
#define digitalPinToBitMask(P) (_BV(P))
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) (&PORTB)
#define portInputRegister(P)  (&PINB)
#define portModeRegister(P)   (&DDRB)

#define NUM_DIGITAL_PINS 6
#define NUM_ANALOG_PINS 4

static const uint8_t MOSI = 0;
static const uint8_t MISO = 1;
static const uint8_t SCK  = 2;

static const uint8_t A0 = 5;
static const uint8_t A1 = 2;
static const uint8_t A2 = 4;
static const uint8_t A3 = 3;

#endif//Pins_Arduino_h
