#include "ESP32Diagnostics.h"
#include "esp_heap_caps.h"
#include "esp_chip_info.h"
#include <WiFi.h>

ESP32Diagnostics::Report ESP32Diagnostics::collect() {
  Report r;
  r.freeHeap = ESP.getFreeHeap();
  r.totalPsram = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
  r.freePsram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
  r.flashSize = ESP.getFlashChipSize();
  r.cpuMHz = ESP.getCpuFreqMHz();
  esp_chip_info_t info{};
  esp_chip_info(&info);
  r.chipRevision = info.revision;
  return r;
}

void ESP32Diagnostics::printSystem(Stream &out) {
  Report r = collect();
  out.println("================================");
  out.println(" ESP32 DIAGNOSTICS");
  out.println("================================");
  out.printf("Chip        : %s\n", ESP.getChipModel());
  out.printf("Revision    : %d\n", r.chipRevision);
  out.printf("CPU         : %lu MHz\n", (unsigned long)r.cpuMHz);
  out.printf("Flash       : %lu MB\n", (unsigned long)(r.flashSize / (1024UL*1024UL)));
  out.printf("Free heap   : %lu bytes\n", (unsigned long)r.freeHeap);
  out.printf("PSRAM total : %lu bytes\n", (unsigned long)r.totalPsram);
  out.printf("PSRAM free  : %lu bytes\n", (unsigned long)r.freePsram);
  out.print(wifiSummary());
  out.println("================================");
}

bool ESP32Diagnostics::scanI2C(TwoWire &wire, Stream &out, uint8_t first, uint8_t last) {
  bool found = false;
  for (uint8_t addr=first; addr<=last; ++addr) {
    wire.beginTransmission(addr);
    if (wire.endTransmission() == 0) { out.printf("I2C: 0x%02X\n", addr); found=true; }
    delay(1);
    if (addr == 0x77) break;
  }
  return found;
}

int ESP32Diagnostics::readGPIO(int pin) { pinMode(pin, INPUT); return digitalRead(pin); }
bool ESP32Diagnostics::writeGPIO(int pin, bool high) { pinMode(pin, OUTPUT); digitalWrite(pin, high ? HIGH : LOW); return true; }

String ESP32Diagnostics::wifiSummary() {
  String s = "WiFi mode   : " + String((int)WiFi.getMode()) + "\n";
  s += "WiFi status : " + String((int)WiFi.status()) + "\n";
  if (WiFi.getMode() == WIFI_AP || WiFi.getMode() == WIFI_AP_STA) s += "AP IP       : " + WiFi.softAPIP().toString() + "\n";
  if (WiFi.getMode() == WIFI_STA || WiFi.getMode() == WIFI_AP_STA) s += "STA IP      : " + WiFi.localIP().toString() + "\n";
  return s;
}
