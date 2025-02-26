# Water Tank Automation

This repository contains the implementation of a Bluetooth-controlled automated water tank system designed for efficient irrigation and water management. The system leverages affordable and accessible hardware components to monitor and control water levels autonomously, with the added convenience of remote operation via a Bluetooth-connected mobile device.

## Overview

The Water Tank Automation system integrates an Arduino Uno with various components to create a sustainable solution for managing water levels in a tank. It uses an ultrasonic sensor to monitor water levels, a relay module to control a 5V water pump, and a Bluetooth module for wireless communication. The system operates based on predefined thresholds and user inputs, making it both autonomous and user-friendly.

### Key Features
- **Autonomous Operation**: Automatically turns the water pump on/off based on water level thresholds detected by the ultrasonic sensor.
- **Bluetooth Control**: Allows remote activation/deactivation of the system via a mobile device.
- **Low Power**: Operates with a 5V water pump and a 9V battery for the Arduino, ensuring energy efficiency.
- **Cost-Effective**: Built with affordable components like the Arduino Uno and HC-05 Bluetooth module.
- **Sustainable**: Reduces water wastage by maintaining optimal water levels.

## Hardware Components
- **Arduino Uno Board**: The central microcontroller managing all operations.
- **Ultrasonic Sensor**: Measures water levels in the tank.
- **5V Water Pump**: Pumps water into the tank when triggered.
- **9V Battery**: Powers the Arduino Uno.
- **Relay Module**: Controls the water pump's power supply.
- **Bluetooth Module (HC-05)**: Enables wireless communication with a mobile device.
- **Latex Tube**: Connects to the water pump for water flow.
- **Jumper Wires**: Used for all connections between components.

## System Design

### Connections
- **Arduino to Relay**: Digital Pin 2 → IN pin of the relay; VCC and Ground supplied by Arduino.
- **Ultrasonic Sensor**: Trigger Pin → Digital Pin 9; Echo Pin → Digital Pin 10; VCC and Ground from Arduino.
- **Bluetooth Module**: TxD → Digital Pin 4; RxD → Digital Pin 5; VCC and Ground from Arduino.
- **Water Pump**: Positive end → Relay; Negative end → Ground; Relay powered with an additional 5V via breadboard.
- **Power**: Arduino powered by a 9V battery.

### How It Works
1. The ultrasonic sensor continuously monitors the water level in the tank.
2. If the water level drops below the lower threshold (e.g., 2 cm), the relay activates the 5V water pump to fill the tank.
3. The pump stops when the water level reaches the upper threshold (e.g., 11 cm).
4. The Bluetooth module connects to a mobile app, allowing users to manually turn the system on or off remotely.

## Results
Field trials demonstrated the system's effectiveness:
- Water pump activated at a 1 cm water level (below the 2 cm threshold) and stopped at 11 cm (total tank height: 12 cm).
- Bluetooth connectivity successfully toggled the relay and pump via a mobile device.
- The system reduced water wastage by maintaining precise levels.

## Installation
1. **Hardware Setup**:
   - Connect all components as described in the "Connections" section.
   - Ensure the ultrasonic sensor is mounted at the top of the tank.
2. **Software Setup**:
   - Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
   - Write or upload the control code to the Arduino Uno via USB.
3. **Mobile App**:
   - Use any Bluetooth terminal app (e.g., "Bluetooth Terminal HC-05") to connect to the HC-05 module and send commands.

## Usage
- Power the Arduino with a 9V battery or USB.
- Pair your mobile device with the HC-05 Bluetooth module.
- Use the app to send ON/OFF commands or let the system run autonomously based on sensor data.

## Future Improvements
- Add a display for real-time water level monitoring.
- Integrate Wi-Fi for internet-based control.
- Enhance power efficiency with solar charging.

## References
- F. Jan and S. Saeed, "IoT-based solutions to monitor water level, leakage, and motor control for smart water tanks," vol. 14, no. 3, p. 309, 2022.
- M. Jan and M. Pan, "Wireless sensor network deployment for water use efficiency in irrigation," vol. 2, no. 3, pp. 46-50, 2008.
- Robitgee, "Control a water pump by Arduino," [link](https://www.robitgee.tech/robotics/control-a-water-pump-by-arduino/), December 2023.

## Contact
For inquiries, reach out to [itstahir256@gmail.com](mailto:itstahir256@gmail.com).
