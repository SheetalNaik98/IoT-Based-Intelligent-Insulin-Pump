# IoT-Based-Intelligent-Insulin-Pump

An IoT-enabled non-invasive insulin regulation system integrating NIR-based glucose monitoring with real-time infusion control using Arduino and mobile interfaces.




---

## Project Summary

Diabetes patients face the burden of frequent blood glucose testing and insulin injections. This system leverages Near-Infrared (NIR) sensors, Wi-Fi-enabled microcontrollers, and mobile interfaces to automatically:
- Detect blood glucose levels non-invasively
- Transmit readings to a smartphone
- Trigger insulin delivery via a DC motor-powered syringe pump

---

## 🔧 Hardware Components

- 🧠 Arduino UNO
- 🔬 NIR Sensor (IR TX/RX Pair)
- 📟 LCD Display (16x2)
- 📡 ESP8266 Wi-Fi Module
- ⚙️ DC Motor + Syringe Driver
- 🔌 L293D H-Bridge Motor Driver
- 🔋 LM7805 Voltage Regulator
- 🧰 Power Supply: 12V Adapter

---

## 💻 Software & Tools

- Arduino IDE (Embedded C)
- Streamlit (Python UI simulation)
- Proteus / Fritzing for circuit design
- Python 3.x for mock interface

---

## How It Works

1. **Non-invasive glucose detection** using IR absorption logic
2. **Signal processing** through Arduino Uno
3. **Wireless communication** to mobile interface via ESP8266
4. **Motor-driven insulin delivery** triggered via app
5. **Real-time monitoring** through LCD + optional mobile app

---
<img width="502" alt="Screenshot 2025-05-25 at 11 01 42 AM" src="https://github.com/user-attachments/assets/0af81317-9bdf-4e45-8c8d-5297bd3b03af" />

## 📄 Arduino Code

```cpp
#include <LiquidCrystal.h>
const int IR_sensor_pin = A0;
const int motorPin = 9;
const int threshold = 130;

void setup() {
  pinMode(IR_sensor_pin, INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int glucoseValue = analogRead(IR_sensor_pin);
  Serial.println(glucoseValue);

  if (glucoseValue > threshold) {
    digitalWrite(motorPin, HIGH);
    delay(2000);
    digitalWrite(motorPin, LOW);
  }

  delay(5000);
}

