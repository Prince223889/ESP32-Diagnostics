#include <ESP32-Diagnostics.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  ESP32Diagnostics::printSystem();
  Wire.begin(7, 8, 400000);
  Serial.println("I2C addresses:");
  ESP32Diagnostics::scanI2C(Wire, Serial);
}
void loop() { delay(5000); }
