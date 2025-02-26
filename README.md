# Water Tank Automation

This repository contains the implementation of a Bluetooth-controlled automated water tank system designed for efficient irrigation and water management. The system combines an Arduino Uno with an ultrasonic sensor, a relay module, a 5V water pump, and a Bluetooth module to monitor and maintain water levels autonomously or via remote commands from a mobile device.

## Overview

The Water Tank Automation system is built to optimize water usage by automatically controlling a water pump based on tank levels or user input. It uses an ultrasonic sensor to measure water levels, a relay to switch the pump, and an HC-05 Bluetooth module for wireless communication. The system supports both automatic and manual modes, making it versatile for various applications like irrigation, hydroponics, or DIY water management projects.

### Key Features
- **Automatic Mode**: Maintains water levels between a lower threshold (2 cm) and an upper threshold (11 cm) using sensor data.
- **Manual Mode**: Allows remote control of the pump via Bluetooth commands from a mobile device.
- **Reliable Measurements**: Averages multiple ultrasonic readings for accurate water level detection.
- **Bluetooth Status Updates**: Sends real-time tank level, pump status, and mode to a connected device.
- **Low-Cost Design**: Utilizes affordable components like the Arduino Uno and a 5V USB-powered pump.

## Hardware Components
- **Arduino Uno Board**: Core microcontroller for processing and control.
- **Ultrasonic Sensor**: Measures the distance to the water surface (max range: 200 cm).
- **5V Water Pump**: Pumps water into the tank, powered via a relay.
- **9V Battery**: Powers the Arduino Uno.
- **Relay Module**: Switches the 5V pump on/off.
- **Bluetooth Module (HC-05)**: Enables wireless communication with a mobile device.
- **Latex Tube**: Connects to the water pump for water flow.
- **Jumper Wires**: Used for all connections.

## System Design

### Hardware Connections
- **Arduino to Relay**: Digital Pin 2 → IN pin; VCC and Ground from Arduino.
- **Ultrasonic Sensor**: Trigger Pin → Digital Pin 9; Echo Pin → Digital Pin 10; VCC and Ground from Arduino.
- **Bluetooth Module**: TxD → Digital Pin 4; RxD → Digital Pin 5; VCC and Ground from Arduino.
- **Water Pump**: Positive end → Relay; Negative end → Ground; Relay powered with an additional 5V via breadboard.
- **Power**: Arduino powered by a 9V battery.

### Software Functionality
The Arduino code (`Water_Tank_Automation.ino`) manages the system with the following logic:
1. **Water Level Monitoring**: The ultrasonic sensor pings every second (configurable via `PING_INTERVAL`), averaging 3 samples for reliability.
2. **Automatic Control**: 
   - If the water level drops below 2 cm (converted to percentage), the pump turns ON.
   - If the level exceeds 11 cm (tank height: 12 cm), the pump turns OFF.
3. **Manual Control**: Bluetooth commands (`1` for ON, `0` for OFF) override automatic mode.
4. **Mode Switching**: Command `A` enables automatic mode; manual mode is activated by pump commands.
5. **Status Reporting**: Command `S` or periodic updates send tank level (%), pump state (ON/OFF), and mode (AUTO/MANUAL) via Bluetooth.

## Results
Testing showed:
- The pump activated when the water level dropped to 1 cm (below the 2 cm threshold) and stopped at 11 cm.
- Bluetooth commands successfully toggled the pump and switched modes.
- The system maintained water levels efficiently, reducing wastage in a 12 cm tank.

## Installation
1. **Hardware Setup**:
   - Assemble components as per the "Hardware Connections" section.
   - Mount the ultrasonic sensor at the top of the tank, facing the water surface.
2. **Software Setup**:
   - Install the [Arduino IDE](https://www.arduino.cc/en/software).
   - Install the `NewPing` library (via Library Manager) for ultrasonic sensor support.
   - Upload `Water_Tank_Automation.ino` from the `src/` folder to the Arduino via USB.
3. **Mobile App**:
   - Use a Bluetooth terminal app (e.g., "Bluetooth Terminal HC-05") to connect to the HC-05 module.
   - Send commands: `1` (pump ON), `0` (pump OFF), `A` (auto mode), `S` (status).

## Usage
- Power the Arduino with a 9V battery or USB.
- Pair your mobile device with the HC-05 module (default PIN: 1234 or 0000).
- Monitor Serial output (115200 baud) or Bluetooth updates for system status.
- Use the app to send commands or let the system run autonomously.
- To use this with your Android app, you'll need to ensure it can send the commands '0', '1', 'A', and 'S' to control the system and receive the status updates.

## Future Improvements
- Add an LCD for local water level display.
- Implement Wi-Fi for cloud-based monitoring.
- Use a solar panel for sustainable power.

## References
- F. Jan and S. Saeed, "IoT-based solutions to monitor water level, leakage, and motor control for smart water tanks," vol. 14, no. 3, p. 309, 2022.
- M. Jan and M. Pan, "Wireless sensor network deployment for water use efficiency in irrigation," vol. 2, no. 3, pp. 46-50, 2008.
- Robitgee, "Control a water pump by Arduino," [link](https://www.robitgee.tech/robotics/control-a-water-pump-by-arduino/), December 2023.

## Contact
For inquiries, reach out to [itstahir256@gmail.com](mailto:itstahir256@gmail.com).
