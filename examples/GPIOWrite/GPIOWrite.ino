#include <ESP32-Diagnostics.h>

static constexpr int GPIO_TO_WRITE = -1;

void setup() {
  Serial.begin(115200);
  delay(300);
  if (!ESP32Diagnostics::canOutputGPIO(GPIO_TO_WRITE)) {
    Serial.println("Set GPIO_TO_WRITE to a valid, board-safe output GPIO first.");
    return;
  }
  pinMode(GPIO_TO_WRITE, OUTPUT);
}

void loop() {
  static bool state = false;
  state = !state;
  Serial.printf("GPIO=%d write=%s result=%s\n", GPIO_TO_WRITE, state ? "HIGH" : "LOW",
                ESP32Diagnostics::writeGPIO(GPIO_TO_WRITE, state) ? "OK" : "FAIL");
  delay(1000);
}
