#include <NewPing.h>
#include <SoftwareSerial.h>

// Pin definitions
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define RELAY_PIN 2
#define BLUETOOTH_TX 4
#define BLUETOOTH_RX 5

// Constants
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters)
#define LOWER_THRESHOLD 2 // Lower water level threshold (in centimeters)
#define UPPER_THRESHOLD 11 // Upper water level threshold (in centimeters)
#define TANK_HEIGHT 12 // Total height of the tank in centimeters
#define PING_INTERVAL 1000 // Time between sensor readings in milliseconds
#define NUM_SAMPLES 3 // Number of samples to average for more reliable readings

// Variables
unsigned long lastPingTime = 0;
bool pumpStatus = false;
bool autoMode = true; // Default to automatic mode
int waterLevelPercentage = 0;

// Objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure the relay is off initially
  
  // Initial message
  Serial.println("Water Tank Automation System Initialized");
  bluetooth.println("Water Tank Automation System Ready");
  
  // Initial reading of water level
  getWaterLevel();
  sendStatusToBluetooth();
}

void loop() {
  // Check water level at regular intervals
  if (millis() - lastPingTime >= PING_INTERVAL) {
    getWaterLevel();
    
    // Automatic control mode
    if (autoMode) {
      if (waterLevelPercentage <= (LOWER_THRESHOLD * 100 / TANK_HEIGHT)) {
        turnPumpOn();
      } else if (waterLevelPercentage >= (UPPER_THRESHOLD * 100 / TANK_HEIGHT)) {
        turnPumpOff();
      }
    }
    
    // Update status via Bluetooth and Serial
    sendStatusToBluetooth();
    lastPingTime = millis();
  }
  
  // Handle Bluetooth commands
  handleBluetoothCommands();
}

// Get water level with multiple readings for reliability
void getWaterLevel() {
  unsigned int totalDistance = 0;
  int validReadings = 0;
  
  // Take multiple samples
  for (int i = 0; i < NUM_SAMPLES; i++) {
    unsigned int distance = sonar.ping_cm();
    if (distance > 0 && distance <= TANK_HEIGHT) {
      totalDistance += distance;
      validReadings++;
    }
    delay(50); // Short delay between readings
  }
  
  // Calculate average if we have valid readings
  if (validReadings > 0) {
    unsigned int avgDistance = totalDistance / validReadings;
    // Convert distance to water level percentage (inverted)
    // When tank is full, distance is small
    // When tank is empty, distance is large
    waterLevelPercentage = map(avgDistance, TANK_HEIGHT, 0, 0, 100);
    waterLevelPercentage = constrain(waterLevelPercentage, 0, 100); // Ensure within range
    
    Serial.print("Water Level: ");
    Serial.print(avgDistance);
    Serial.print(" cm (");
    Serial.print(waterLevelPercentage);
    Serial.println("%)");
  } else {
    Serial.println("Error: Could not get valid water level readings");
  }
}

// Turn the water pump on
void turnPumpOn() {
  if (!pumpStatus) {
    digitalWrite(RELAY_PIN, HIGH);
    pumpStatus = true;
    Serial.println("Water pump turned ON");
  }
}

// Turn the water pump off
void turnPumpOff() {
  if (pumpStatus) {
    digitalWrite(RELAY_PIN, LOW);
    pumpStatus = false;
    Serial.println("Water pump turned OFF");
  }
}

// Process incoming Bluetooth commands
void handleBluetoothCommands() {
  while (bluetooth.available()) {
    char command = bluetooth.read();
    
    switch (command) {
      case '1': // Turn pump ON
        autoMode = false; // Switch to manual mode
        turnPumpOn();
        Serial.println("Manual mode: Water pump turned ON via Bluetooth");
        break;
        
      case '0': // Turn pump OFF
        autoMode = false; // Switch to manual mode
        turnPumpOff();
        Serial.println("Manual mode: Water pump turned OFF via Bluetooth");
        break;
        
      case 'A': // Enable automatic mode
        autoMode = true;
        Serial.println("Automatic mode enabled via Bluetooth");
        break;
        
      case 'S': // Request status update
        sendStatusToBluetooth();
        break;
        
      default:
        // Ignore unknown commands
        break;
    }
  }
}

// Send current status to Bluetooth device
void sendStatusToBluetooth() {
  String status = "Status:";
  status += " Level:" + String(waterLevelPercentage) + "%";
  status += " Pump:" + String(pumpStatus ? "ON" : "OFF");
  status += " Mode:" + String(autoMode ? "AUTO" : "MANUAL");
  
  bluetooth.println(status);
}
