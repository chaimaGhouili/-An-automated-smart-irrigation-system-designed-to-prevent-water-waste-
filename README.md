
![Design sans titre (1)](https://github.com/user-attachments/assets/d9f952c4-a719-4145-ba1d-388c1cffd4ec)
# 🌱 Smart Irrigation System with ESP32

This project implements an **automated smart irrigation system** designed to **prevent water waste**. It uses an **ESP32 microcontroller** and several sensors to monitor environmental conditions and control a water pump.

## 🚀 Features

- 🌡️ Monitors soil moisture, air temperature, air humidity
- 🧠 Dual mode: Manual & Automatic
- 💧 Controls irrigation based on real-time sensor data
- 📱 Remote control and monitoring via **Blynk app**
- 🔊 Ultrasonic sensor checks water level in the reservoir
- 🔴 Status indication using onboard LEDs

## ⚙️ Components

- ESP32
- DHT11 (Temperature & Humidity sensor)
- Soil Moisture Sensor
- Ultrasonic Sensor (HC-SR04)
- Relay Module
- Water Pump
- LEDs (for status)
- Resistors & Wires
- Breadboard
**Schematic wiring : **
A schematic diagram is provided using **circuito.io** to visualize connections between ESP32 and sensors.
![1](https://github.com/user-attachments/assets/c16768bd-822c-497f-a5c4-397cb803b5ae)

## 🧠 How It Works

- In **manual mode**, the user controls the pump via the Blynk app.
- In **automatic mode**, the ESP32 checks:
  - Soil moisture
  - Temperature
  - Air humidity
  - Water level
- Depending on these factors, it activates the pump for a short or long period.
- LED indicators show whether the system is idle or watering.
  **Real wiring :**
![Design sans titre (1)](https://github.com/user-attachments/assets/d9f952c4-a719-4145-ba1d-388c1cffd4ec)
## 📲 Blynk Setup

- Use **Blynk Legacy** or **Blynk IoT**
- Add virtual pins:
  - `V0` – Soil Moisture
  - `V1` – Manual Pump Control
  - `V4` – Mode Selection (Manual/Auto)
  - `V5` – Air Humidity
  - `V6` – Temperature
  - `V7` – Water Level
  - `V9`, `V10`, `V11` – LED Status Indicators
![Votre texte de paragraphe](https://github.com/user-attachments/assets/27d5f007-0a8d-4912-8a03-98895e8ffaf8)


## 📁 Files

- `main.ino`: Arduino code for ESP32
- `README.md`: Project documentation

## ✅ Requirements

- Arduino IDE
- Blynk Library
- ESP32 Board Package

## 📜 Contact

👩‍💻 **Chaima Ghouili**  
🔗 [LinkedIn Profile](https://www.linkedin.com/in/chaima-ghouili-98b54527a/)
📧 Email: *[chaima.ghouili@isimg.tn]* 

---


