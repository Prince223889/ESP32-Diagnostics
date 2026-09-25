#pragma once
#include <Arduino.h>
#include <Wire.h>

class ESP32Diagnostics {
public:
  struct Report {
    uint32_t freeHeap = 0;
    uint32_t totalPsram = 0;
    uint32_t freePsram = 0;
    uint32_t flashSize = 0;
    uint32_t cpuMHz = 0;
    int chipRevision = 0;
  };

  static Report collect();
  static void printSystem(Stream &out = Serial);
  static bool scanI2C(TwoWire &wire, Stream &out, uint8_t first=0x03, uint8_t last=0x77);
  static int readGPIO(int pin);
  static bool writeGPIO(int pin, bool high);
  static String wifiSummary();
};
