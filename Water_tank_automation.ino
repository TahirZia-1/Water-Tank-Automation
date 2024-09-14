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

// Objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure the relay is off initially
  Serial.println("Water Tank Automation System Initialized");
}

void loop() {
  delay(50); // Wait 50ms between pings (about 20 pings/sec)
  unsigned int distance = sonar.ping_cm();

  if (distance > 0) {
    Serial.print("Water Level: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= LOWER_THRESHOLD) {
      digitalWrite(RELAY_PIN, HIGH); // Turn on the water pump
      Serial.println("Water pump turned ON");
    } else if (distance >= UPPER_THRESHOLD) {
      digitalWrite(RELAY_PIN, LOW); // Turn off the water pump
      Serial.println("Water pump turned OFF");
    }
  } else {
    Serial.println("Out of range");
  }

  // Bluetooth control
  if (bluetooth.available()) {
    char command = bluetooth.read();
    if (command == '1') {
      digitalWrite(RELAY_PIN, HIGH); // Turn on the water pump
      Serial.println("Water pump turned ON via Bluetooth");
    } else if (command == '0') {
      digitalWrite(RELAY_PIN, LOW); // Turn off the water pump
      Serial.println("Water pump turned OFF via Bluetooth");
    }
  }
}
