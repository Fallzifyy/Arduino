int SensorLED = 13;       // LED Pin
int SensorINPUT = 3;      // Sensor Pin (digital Pin 3 for interrupt)
volatile unsigned int triggerCount = 0;  // Count the number of sensor triggers
unsigned long startTime = 0;    // Store the start time for monitoring

// User-configurable settings
const unsigned int alarmThreshold =4 ;    // Set the number of sensor triggers to trigger alarm
const unsigned long timeWindow = 10000;   // Time window in milliseconds (e.g., 10 seconds)
void setup() {
  pinMode(SensorLED, OUTPUT);
  pinMode(SensorINPUT, INPUT);
  
  // Use digitalPinToInterrupt for compatibility across boards
  attachInterrupt(digitalPinToInterrupt(SensorINPUT), blink, RISING);
  
  Serial.begin(9600);           // For debugging or user feedback
  startTime = millis();          // Initialize the start time
}

void loop() {
  // Check if the time window has passed
  if (millis() - startTime >= timeWindow) {
    if (triggerCount >= alarmThreshold) {
      triggerAlarm();           // Trigger the alarm if threshold is met
    }
    // Reset the start time and trigger count after the time window
    startTime = millis();
    triggerCount = 0;
  }
}

// Interrupt Service Routine (ISR)
void blink() {
  triggerCount++;               // Increment trigger count on each sensor activation
}

// Function to trigger the alarm
void triggerAlarm() {
  // Blink the LED rapidly to indicate an alarm
  for (int i = 0; i < 10; i++) {
    digitalWrite(SensorLED, HIGH);
    delay(100);                 // 100ms ON
    digitalWrite(SensorLED, LOW);
    delay(100);                 // 100ms OFF
  }
  Serial.println("Alarm Triggered!");  // Output to serial monitor
}

