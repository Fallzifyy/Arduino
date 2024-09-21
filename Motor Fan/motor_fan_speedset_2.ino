#include <LedControl.h>

const int buttonPinIncrease = 2;    // Button to increase speed
const int buttonPinDecrease = 3;    // Button to decrease speed
const int motorPin = 9;             // Motor control pin (PWM)

int motorSpeed = 0;                 // Motor speed (0-255 for PWM)
const int maxSpeed = 255;           // Max PWM value
const int minSpeed = 0;             // Min PWM value

// LED matrix settings
const int dataIn = 12;
const int clk = 11;
const int load = 10;
LedControl lc = LedControl(dataIn, clk, load, 1); // 1 is the number of LED displays

void setup() {
  // Initialize LED Matrix
  lc.shutdown(0, false);            // Wake up the LED matrix
  lc.setIntensity(0, 8);            // Set brightness level (0-15)
  lc.clearDisplay(0);               // Clear the display
  
  // Set up buttons
  pinMode(buttonPinIncrease, INPUT_PULLUP); // Pull-up resistor for increase button
  pinMode(buttonPinDecrease, INPUT_PULLUP); // Pull-up resistor for decrease button
  
  // Set up motor control pin
  pinMode(motorPin, OUTPUT);        // Set motor pin as output
  analogWrite(motorPin, motorSpeed); // Set initial motor speed
  
  Serial.begin(9600);               // Initialize serial for debugging
}

void loop() {
  // Read button states (no debounce for simplicity)
  if (digitalRead(buttonPinIncrease) == LOW) {  // Increase speed when button is pressed
    motorSpeed = min(motorSpeed + 25, maxSpeed); // Increase speed in steps of 25
    updateMotorSpeed();
  }
  
  if (digitalRead(buttonPinDecrease) == LOW) {  // Decrease speed when button is pressed
    motorSpeed = max(motorSpeed - 25, minSpeed); // Decrease speed in steps of 25
    updateMotorSpeed();
  }
  
  // Update LED matrix to show motor speed (0-9)
  displaySpeed(motorSpeed / 25);  // Display speed as a single digit (0-9)
}

void updateMotorSpeed() {
  analogWrite(motorPin, motorSpeed);  // Set motor speed using PWM
  Serial.print("Motor speed: ");
  Serial.println(motorSpeed);
}

void displaySpeed(int speed) {
  lc.clearDisplay(0);  // Clear the LED matrix display
  lc.setDigit(0, 0, speed, false);  // Display the speed as a single digit (0-9)
}
