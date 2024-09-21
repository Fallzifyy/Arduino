#include <IRremote.h>

const int redPin = 9;           // R – digital 9
const int greenPin = 10;        // G – digital 10
const int bluePin = 11;         // B – digital 11
const int RECV_PIN = 3;         // IR receiver pin

IRrecv irrecv(RECV_PIN);        // Create IR receiver object
decode_results results;

// Define button codes (replace with your actual remote codes)
const unsigned long RED_BUTTON = 0xFF30CF;
const unsigned long GREEN_BUTTON = 0xFF18E7;
const unsigned long BLUE_BUTTON = 0xFF7A85;
const unsigned long OFF_BUTTON = 0xFF38C7;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  irrecv.enableIRIn();          // Start the IR receiver
}

void loop() {
  if (irrecv.decode(&results)) {   // If an IR signal is received
    switch (results.value) {
      case RED_BUTTON:   // Red color
        colorRGB(255, 0, 0);
        break;
      case GREEN_BUTTON: // Green color
        colorRGB(0, 255, 0);
        break;
      case BLUE_BUTTON:  // Blue color
        colorRGB(0, 0, 255);
        break;
      case OFF_BUTTON:   // Turn off (all LEDs off)
        colorRGB(0, 0, 0);
        break;
    }
    irrecv.resume();  // Receive the next value
  }
}

// Set the RGB color
void colorRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
