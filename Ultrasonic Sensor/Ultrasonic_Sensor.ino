#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 4;

Servo myServo;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  
  // Set the sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo
  myServo.attach(servoPin);
  
  // Set initial position of the servo
  myServo.write(0); // start at 0 degree
}

void loop() {
  // Rotate the servo from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(15); // Allow the servo to move to the position

    // Measure the distance using the ultrasonic sensor
    distance = measureDistance();
    
    // Send the distance value to the Processing IDE
    Serial.print("Angle: ");
    Serial.print(pos);
    Serial.print(" Distance: ");
    Serial.println(distance);

    delay(100); // Wait before scanning again
  }
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (in cm)
  distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/us
  
  return distance;
}

