#include <ESP32Diagnostics.h>

void setup() {
  Serial.begin(115200);
  delay(300);
  ESP32Diagnostics::printSystem();
}

void loop() { delay(5000); }
