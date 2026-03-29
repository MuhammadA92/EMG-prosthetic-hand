# EMG-Controlled Prosthetic Hand

## Overview
This project involves the development of a multi-axis prosthetic hand as part of the Prosthetics Society at Imperial College London. The system is designed to interpret muscle signals from the user and translate them into controlled hand movement.

The prosthetic hand consists of three fingers and is mechanically designed and 3D printed by the mechanical team. As part of the electrical team, I contributed to the signal sensing, control logic, communication, and wider electrical system integration.

## My Role
I worked within the electrical team, contributing to:

- Signal sensing and amplification considerations for muscle-based input  
- Control logic for prosthetic actuation  
- Wireless communication between microcontrollers  
- Motor, power, and embedded systems integration  

This project sits at the intersection of electronics, control systems, and embedded programming, with the overall goal of converting biological signals into reliable mechanical movement.

## System Architecture
The current prototype uses two Arduino boards to separate signal/control tasks before transitioning to smaller embedded hardware such as Arduino Nano boards.

### 1. Sender / Control Board
- Scans for and connects to the receiving board over BLE
- Sends control commands wirelessly

### 2. Receiver / Actuation Board
- Advertises a BLE service and characteristic
- Receives commands from the sender board
- Triggers output behaviour that can later be extended to hand actuation

This wireless architecture supports modular testing during development and helps separate control and actuation stages.

## Code Implementation
The repository includes both sides of the BLE communication system:

- `code/ble_sender.ino` → central device code that scans, connects, and writes control values
- `code/ble_receiver.ino` → peripheral device code that advertises the BLE service and responds to incoming values

The receiver sets up a BLE service and characteristic and listens for written values. The sender scans for the service UUID, connects, discovers the matching characteristic, and writes values to control the receiver state.

At this stage, the example implementation toggles an LED to verify reliable communication between the two boards. This acts as a hardware testbed before integrating the same communication structure into the prosthetic hand control system.

## Engineering Approach
A key challenge in this project is converting noisy biological signals into stable and responsive control inputs.

The wider system design considers:
- signal sensing from different muscle groups
- amplification and conditioning of small input signals
- robust communication between embedded devices
- motor control for multi-axis movement
- future extension to features such as a hold/grip function

The project is intended to evolve from proof-of-concept communication and actuation testing into a more complete prosthetic control system.

## Future Improvements
- Integrate real sensor-driven muscle inputs into the BLE control logic
- Implement a hold function for sustained grip
- Improve movement mapping and control smoothness
- Transition from Arduino Uno boards to Arduino Nano boards
- Expand actuation capability and control resolution

## Repository Structure
- `/code` → Arduino BLE sender and receiver code
- `README.md` → project overview and system explanation

## What I Learned
- Embedded systems programming with Arduino / C++
- BLE communication between microcontrollers
- Hardware-software integration
- Control-system thinking for assistive technology
- Working in a multidisciplinary engineering team
