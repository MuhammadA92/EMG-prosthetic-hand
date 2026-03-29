# EMG-prosthetic-hand
EMG-based prosthetic hand using Arduino, with wireless communication and motor control for multi-axis movement.

## Overview
This project involves the development of a multi-axis prosthetic hand as part of the Prosthetics Society at Imperial College London. The system is designed to interpret muscle signals from the user and translate them into controlled hand movement.

The prosthetic hand consists of three fingers and is mechanically designed and 3D printed by the mechanical team. As part of the electrical team, I contributed to the signal processing, control logic, and system integration.

## My Role
I worked within the electrical team, focusing on:

- Developing control logic for hand movement  
- Supporting signal acquisition and processing from muscle input  
- Implementing communication between microcontrollers  
- Contributing to motor control and system integration  

My work involved bridging the gap between biological signal input and physical actuation.

## System Architecture

The system is built around two microcontrollers (Arduino-based):

### 1. Signal Acquisition Unit
- Receives muscle signals (via sensors and amplification circuits)  
- Processes signals into usable control inputs  

### 2. Control & Actuation Unit
- Receives processed signals  
- Drives motors to control finger movement  

Communication between these units is currently implemented wirelessly, allowing modular testing and flexibility in system design.

## Control Implementation

The system uses wireless communication (BLE-based) to transmit control signals between devices.

Example implementation:

```cpp
// BLE communication example (simplified)
ledCharacteristic.writeValue((byte)0x01); // Activate movement
ledCharacteristic.writeValue((byte)0x00); // Stop movement
