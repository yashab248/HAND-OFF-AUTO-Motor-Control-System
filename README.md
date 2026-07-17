# HAND-OFF-AUTO Motor Control System 🟢🔴🔵
<img width="1000" height="500" alt="CIRCUIT-SCHEMATIC-HOA-CONTROL" src="https://github.com/user-attachments/assets/03b3b92b-43e7-4687-9038-fa7a2476b3ae" />

## Overview

This project is a microcontroller-based motor control system designed to replicate industrial HAND-OFF-AUTO operation commonly used in motor control applications.

The system allows an operator to select between three operating modes:

- **HAND Mode:** Manual motor speed control using a potentiometer input.
- **AUTO Mode:** Automatic motor speed adjustment based on temperature sensor feedback.
- **OFF/ESD Mode:** Emergency shutdown functionality to immediately disable motor operation.

The project combines embedded programming, electrical hardware design, and motor control concepts to create a small-scale prototype of an industrial motor control system.

**DEMO:**

[![Watch Demo](<img width="827" height="479" alt="image" src="https://github.com/user-attachments/assets/5ebd8726-ffa9-4780-9678-2d21101ce688" />
)](https://youtube.com/shorts/huuvXkki1aA?feature=share)

**More demonstrations of project functionality is shown at the bottom.**

---

## Project Motivation

At my Electrical Engineering Internship at Equinox Engineering Ltd., I worked with industrial motor-driven equipment that use HAND-OFF-AUTO control schemes to provide operators with flexibility, automation, and safety features. 

This project was developed to explore how these control strategies can be implemented using a microcontroller-based system while applying concepts in embedded programming, electrical circuits, and motor control.

---

## System Features

### HAND Mode
- Operator manually controls motor speed using a potentiometer.
- Analog input from the potentiometer is converted into a PWM output signal.
- PWM signal controls the motor speed through a transistor switching circuit.

### AUTO Mode
- Temperature sensor provides real-time feedback to the Arduino.
- Motor speed automatically adjusts based on measured temperature.
- Demonstrates closed-loop control concepts.

### OFF/ESD Mode
- Emergency shutdown input disables motor operation.
- Provides a safety mechanism similar to industrial emergency stop systems.
- Can use a reset button to go back to HAND-AUTO-OFF control

---

## Hardware Components

| Component | Purpose |
|-----------|---------|
| Arduino Uno | Main microcontroller |
| 6-12VDC Motor | Controlled motor load |
| NPN Transistor | Motor switching device |
| Flyback Diode | Protects circuit from inductive voltage spikes |
| Potentiometer | Controls motor speed for HAND mode |
| Temperature Sensor (DHT11) | Provides feedback for AUTO mode |
| LCD 16x2 I2C Display | Displays system status |
| 4 Push Buttons | User inputs |
| RGB LED | Mode indicators (HAND: 🟢)(AUTO: 🔵)(ESD: 🔴) |
| 9V Battery Supply | Powers motor circuit |

---

## System Architecture
<p align = "center">
  <img width="500" height="800" alt="Block Diagram for HAND-OFF-AUTO CONTROL PROJECT" src="https://github.com/user-attachments/assets/ea64927f-b50e-4fe1-9cbe-3ee949b0a9b1" />
</p>


Example:

Temperature Sensor  
↓  
Arduino Uno  
↓  
Motor Driver Circuit  
↓  
DC Motor


---

## Circuit Design

The Arduino cannot directly supply enough current to drive the DC motor. A transistor switching circuit was implemented to allow the Arduino to control a higher-current motor load.

Electrical design considerations included:

- Shared ground between Arduino and external motor power supply.
- Flyback diode protection for inductive motor loads.
- Transistor operation as an electronic switch.
- PWM speed control for variable motor operation.
- The DHT11 sensor was chosen over TMP36 because it eliminates the need for analog voltage conversion
<img width="1055" height="816" alt="image" src="https://github.com/user-attachments/assets/03cc6f86-8de8-4d37-8f98-9d2e3948116c" />



---

## Software Design

The Arduino firmware was developed using Embedded C++.

The program performs:

1. Reads user inputs.
2. Determines operating mode.
3. If HAND mode: Reads potentiometer data and converts the PWM signal.
4. If AUTO mode: Reads temperature sensor data and converts the PWM signal.
5. If OFF mode: De-energizes the motor.
6. Calculates motor speed output.
7. Updates LCD display.
8. Controls motor operation.

<p align="center">
  <img width="400" height="900" alt="Flowchart for HAND-OFF-AUTO CONTROL PROJECT (3)" src="https://github.com/user-attachments/assets/dece195f-1b65-4dd2-b33a-7da55a4c8760" />
</p>


---

## Demonstration
PICTURE OF SETUP:

<img width="543" height="407" alt="image" src="https://github.com/user-attachments/assets/893358db-05dc-4dc7-8c8b-06c7296c88fa" />

CLOSE-UP OF BREADBOARD WIRING:

<img width="543" height="407" alt="image" src="https://github.com/user-attachments/assets/48f92cce-61b2-4d8f-b084-11c1caf6a563" />

VIDEO OF HAND FUNCTIONALITY 🟢:

https://youtu.be/bZu68L75NJM

VIDEO OF AUTO FUNCTIONALITY 🔵:



VIDEO OF EMERGENCY SHUTDOWN FUNCTIONALITY 🔴:



Example:

- HAND mode: Manual motor speed adjustment.
- AUTO mode: Temperature-based motor control.
- ESD mode: Emergency motor shutdown.

---

## Skills Demonstrated

- Embedded C/C++ programming
- Arduino development
- PWM motor control
- Analog sensor interfacing
- Transistor switching circuits
- Motor protection techniques
- Human-machine interface (HMI) design
- Electrical troubleshooting
