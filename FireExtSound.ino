#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX

const int buzzerPin = 9; // Connect the buzzer to pin 9
bool fireCommandReceived = false;
unsigned long startTime = 0;
const unsigned long toneDuration = 10000; // Tone duration in ms (10 seconds)

// Function to initialize components
void initializeSystem() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    pinMode(buzzerPin, OUTPUT);
    Serial.println("System ready. Waiting for command...");
}

// Function to generate a high frequency tone (e.g., 10kHz)
void generateFireExtinguishTone() {
    Serial.println("Generating high-frequency tone to extinguish fire...");
    unsigned long currentTime = millis();
    while (millis() - currentTime < toneDuration) {
        digitalWrite(buzzerPin, HIGH);
        delayMicroseconds(50); // 10kHz => 100us period, 50us HIGH
        digitalWrite(buzzerPin, LOW);
        delayMicroseconds(50); // 50us LOW
    }
    Serial.println("Tone generation complete.");
}

// Function to listen for Bluetooth command
void listenForCommand() {
    if (bluetooth.available()) {
        String input = bluetooth.readStringUntil('\n');
        input.trim(); // remove any whitespace
        Serial.print("Received via Bluetooth: ");
        Serial.println(input);
        if (input.equalsIgnoreCase("FIRE")) {
            fireCommandReceived = true;
        }
    }
}

// Setup function
void setup() {
    initializeSystem();
}

// Main loop
void loop() {
    listenForCommand();
    if (fireCommandReceived) {
        generateFireExtinguishTone();
        fireCommandReceived = false; // reset the flag
    }
}