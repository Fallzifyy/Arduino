#include <IRremote.h>

const int RECV_PIN = 11;  // Pin for IR receiver
const int ledPin = 10;    // Pin for LED
bool ledState = LOW;      // Store LED state

IRrecv irrecv(RECV_PIN);  // Create an IR receiver object
decode_results results;   // To store decoded IR results

void setup() {
  Serial.begin(9600);      // Initialize serial communication for debugging
  irrecv.enableIRIn();     // Start the IR receiver
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  digitalWrite(ledPin, ledState); // Initialize LED to OFF
}

void loop() {
  if (irrecv.decode(&results)) {      // Check if an IR signal is received
    Serial.println(results.value, HEX);  // Print the received IR code in hexadecimal

    if (results.value == 0xFD00FF) {  // Toggle LED when the specific IR code is received
      ledState = !ledState;           // Toggle LED state
      digitalWrite(ledPin, ledState); // Set LED state
    }

    irrecv.resume();  // Continue to the next IR signal
  }
}

