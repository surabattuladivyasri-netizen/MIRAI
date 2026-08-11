# MIRAI: An Intelligent Multi-Sensor Navigation Aid for the Visually Impaired

[![Publication](https://img.shields.io/badge/Published-SSRG%20IJCSE-blue)](https://doi.org/10.14445/23488387/1JCSE-V1314P101)
[![Platform](https://img.shields.io/badge/Platform-Arduino%20Mega%202560-green)]()
[![Language](https://img.shields.io/badge/Language-Embedded%20C%2B%2B-orange)]()

**MIRAI** is an IoT-based intelligent assistive smart cane designed to enhance safe, confident, and independent mobility for visually impaired individuals. The system replaces passive traditional white canes with a multi-sensor platform capable of real-time 360° obstacle detection, ground hazard identification (water, pits, stairs), and automatic fall detection.

---

## Documentation & Diagrams

Click the links below to view the system media and schematics:

* 🖼️ [View Hardware Prototype](docs/Stick_Photo.png)
* 📐 [View System Architecture](docs/System_Architecture.png)
* ⚡ [View Circuit Diagram](docs/Circuit_Diagram.png)
* 🔄 [View Workflow Diagram](docs/Workflow_Diagram.png)

---

## Key Features

* **360° Proximity Sensing:** Multi-directional obstacle detection (Front, Left, Right).
* **Ground Hazard Detection:** Identifies water puddles, pits, and stairs using dedicated sensors.
* **Emergency GPS-GSM Alerting:** Automatically transmits live GPS location via SMS upon fall or SOS activation.
* **Gesture & Sound Controls:** Shake-based SOS trigger and clap-based device localization.
* **Audio Feedback:** Real-time directional voice guidance and buzzer warnings.

---

## Code & System Setup

### Source Code
The core embedded program is located in [`src/MIRAI.ino`](src/MIRAI.ino).

### Components Used
* **Microcontroller:** Arduino Mega 2560
* **Sensors:** Ultrasonic Sensors (HC-SR04), Water Level Sensor, MPU6050 IMU, IR Sensor, Sound/Microphone Sensor
* **Communication & Location:** NEO-6M GPS Module, SIM900 GSM Module
* **Audio & Output:** DFPlayer Mini MP3 Module, Active Buzzer
* **Power Supply:** Dual 3.7V Lithium-ion Battery Unit (~7.4V)

---

## Research Publication

This project has been published in the **SSRG International Journal of Computer Science and Engineering (IJCSE)**:
* **Paper Title:** *An Intelligent Multi-Sensor Navigation Aid for Safe and Independent Mobility Among the Visually Impaired*
* **Volume/Issue:** Volume 13 Issue 4, April 2026