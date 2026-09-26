#include <ESP32Diagnostics.h>

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println(ESP32Diagnostics::wifiSummary());
}

void loop() { delay(5000); }
