/*
 * Minimal Software SPI for ATtiny13
 * Defaults to SPI mode 0, msb-first.
 *
 * MIT/X license © 2016 Daniel Lima <danielm@tinyhub.tk>
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

#ifndef SPI_SCK
#define SPI_SCK SCK
#endif
#ifndef SPI_MISO
#define SPI_MISO MISO
#endif
#ifndef SPI_MOSI
#define SPI_MOSI MOSI
#endif

#define SPI_HAS_TRANSACTION 0
#define SPI_HAS_NOTUSINGINTERRUPT 0
#define SPI_ATOMIC_VERSION 0

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

#define SPI_CLOCK_DIV2 0

class SPISettings {
public:
  SPISettings() {}
  SPISettings(uint32_t clock, uint8_t order, uint8_t mode)
  : order(order),
    mode(mode)
  {}

  uint8_t order;
  uint8_t mode;
};

class SPIClass {
public:
  static void begin() {
    pinMode(SPI_SCK,  OUTPUT);
    pinMode(SPI_MOSI, OUTPUT);
    pinMode(SPI_MISO, INPUT);
  }
  static void beginTransaction(const SPISettings &settings = SPISettings()) {
    setBitOrder(settings.order);
    setDataMode(settings.mode);
    cli();
  }
  static uint8_t transfer(uint8_t data) {
    uint8_t r = 0;
    uint8_t bit = SPIClass::msb ? 0x80 : 1;
    while (bit) {
      if (SPIClass::cpah)
        digitalToggle(SPI_SCK);
      digitalWrite(SPI_MOSI, !!(data & bit));
      if (SPIClass::msb) {
        r <<= 1;
        bit >>= 1;
      } else {
        bit <<= 1;
      }
      digitalToggle(SPI_SCK);
      r |= digitalRead(SPI_MISO);
      if (!SPIClass::msb)
        asm("ror %0" : "=r"(r) : "0"(r));
      if (!SPIClass::cpah)
        digitalToggle(SPI_SCK);
    }
    return r;
  }
  static uint16_t transfer16(uint16_t data) {
    uint8_t h = data >> 8;
    uint8_t l = data & 0xFF;
    uint16_t r = transfer(h);
    return (r << 8) | transfer(l);
  }
  static void transfer(void *buf, size_t len) {
    uint8_t *p = (uint8_t*) buf;
    for (int i=0; i<len; i++) {
      p[i] = transfer(p[i]);
    }
  }
  static void endTransaction(void) { sei(); }
  static void end() {}
  static void usingInterrupt(uint8_t intNumber) {}
  static void notUsingInterrupt(uint8_t intNumber) {}
  static void setBitOrder(uint8_t order) {
    SPIClass::msb = order;
  }
  static void setDataMode(uint8_t mode) {
		SPIClass::cpah = bitRead(mode,0);
    digitalWrite(SPI_SCK, bitRead(mode,1) ? HIGH : LOW);
  }
  static void setClockDivider(uint8_t clkDiv) {}
  static void attachInterrupt() {}
  static void detachInterrupt() {}

private:
  static bool msb;
  static bool cpah;
};

extern SPIClass SPI;

#endif
