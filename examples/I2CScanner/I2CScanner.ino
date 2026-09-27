#include <Wire.h>
#include <ESP32-Diagnostics.h>

static constexpr int I2C_SDA = -1;
static constexpr int I2C_SCL = -1;
static constexpr uint32_t I2C_FREQUENCY = 100000;

void setup() {
  Serial.begin(115200);
  delay(300);
  if (I2C_SDA < 0 || I2C_SCL < 0) {
    Serial.println("Set I2C_SDA and I2C_SCL for your board first.");
    return;
  }
  if (!Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQUENCY)) {
    Serial.println("Wire.begin() failed.");
    return;
  }
  ESP32Diagnostics::scanI2C(Wire, Serial);
}

void loop() { delay(5000); }
