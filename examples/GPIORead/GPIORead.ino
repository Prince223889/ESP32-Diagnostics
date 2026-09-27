#include <ESP32-Diagnostics.h>

static constexpr int GPIO_TO_READ = -1;

void setup() {
  Serial.begin(115200);
  delay(300);
  if (!ESP32Diagnostics::isValidGPIO(GPIO_TO_READ)) {
    Serial.println("Set GPIO_TO_READ to a valid, board-safe GPIO first.");
    return;
  }
  pinMode(GPIO_TO_READ, INPUT);
}

void loop() {
  const int value = ESP32Diagnostics::readGPIO(GPIO_TO_READ);
  Serial.printf("GPIO=%d value=%d\n", GPIO_TO_READ, value);
  delay(500);
}
