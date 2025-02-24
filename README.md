## Mecanical Rotary Encoder Library

A lightweight library for handling **mechanical rotary encoders** (e.g., KY-040). It tracks encoder states to **avoid false inputs** and provides accurate rotation detection with **debouncing** and **direction tracking**. Supports easy integration for projects requiring precise encoder input.

Library for handling **mechanical rotary encoders** (e.g., KY-040). It tracks encoder states to **avoid false inputs** and provides accurate rotation detection.

## Example code to use this library

```cpp
#include <Arduino.h>
#include <MechanicalEncoder.h>

// Pin definitions for the rotary encoder
const uint8_t PIN_DT = 25;  // Data pin
const uint8_t PIN_CLK = 26; // Clock pin

// Encoder value range and initial settings
const int ENCODER_MIN_VALUE = 0;     // Minimum encoder value
const int ENCODER_MAX_VALUE = 32;    // Maximum encoder value
const int ENCODER_INITIAL_VALUE = 0; // Starting value of the encoder
const bool ENCODER_LOOP_ENABLED = false; // Whether the encoder loops 

// Create a RotaryEncoder object with the specified settings
MechanicalEncoder encoder1(PIN_DT, PIN_CLK, ENCODER_MIN_VALUE, ENCODER_MAX_VALUE, ENCODER_INITIAL_VALUE, ENCODER_LOOP_ENABLED);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
}

void loop() {
  // Process the encoder and check if its value has changed
  if (encoder1.ProcessAndCheck()) {
    // If the value has changed, print the new value to the serial monitor
    Serial.println(encoder1.Value());
  }
}
```

## Summary of Functions
| Function          | Description                                                                 | Returns                          |
|-------------------|-----------------------------------------------------------------------------|----------------------------------|
| `Process`         | Processes the encoder pin states and updates the encoder's value.           | None                             |
| `Check`           | Checks if the encoder's value has changed since the last `Process` call.    | `true` if changed, `false` otherwise |
| `Value`           | Returns the current value of the encoder.                                  | Current encoder value (integer)  |
| `ProcessAndCheck` | Processes the encoder pin states and checks if the value has changed.       | `true` if changed, `false` otherwise |
