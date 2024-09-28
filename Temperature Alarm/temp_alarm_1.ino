float sinVal;
int toneVal;
unsigned long tepTimer;

void setup() {
    pinMode(8, OUTPUT);     // Buzzer pin
    Serial.begin(9600);     // Start serial communication
}

void loop() {
    int val;
    double data;

    // Read analog value from temperature sensor
    val = analogRead(0);
    
    // Correct temperature conversion formula
    data = (double)val * (5.0 / 10.24);  // Convert voltage to temperature in degrees Celsius

    // Check if the temperature exceeds 27°C
    if (data > 27) {
        // Generate a sound based on a sine wave
        for (int x = 0; x < 180; x++) {
            sinVal = sin(x * (3.1412 / 180));     // Generate sine wave value
            toneVal = 2000 + (int(sinVal * 1000)); // Calculate tone frequency
            tone(8, toneVal);                      // Play the tone on buzzer
            delay(2);                              // Short delay to modulate the sound
        }
    } else {
        noTone(8);  // Stop the buzzer if temperature is below threshold
    }

    // Output the temperature every 500ms
    if (millis() - tepTimer > 500) {
        tepTimer = millis();          // Reset the timer
        Serial.print("Temperature: ");
        Serial.print(data);           // Print temperature to serial monitor
        Serial.println("°C");
    }
}

