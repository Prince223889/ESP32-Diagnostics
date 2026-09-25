# ESP32-Diagnostics

A small, non-destructive diagnostics library for ESP32 boards. It reports chip/memory/flash/PSRAM/CPU information and can inspect an already-initialized I2C bus and Wi-Fi state.

## Principle

It deliberately avoids destructive hardware tests. For GPIO, call `readGPIO()` or `writeGPIO()` on pins you have explicitly assigned. Do not blindly toggle board pins that control flash, PSRAM, the camera, display, USB or power rails.

## Example output

```text
ESP32 DIAGNOSTICS
Chip : ESP32-P4
PSRAM total : ...
PSRAM free  : ...
WiFi mode : ...
```
