#include <LedControl.h>

// Pin connections for MAX7219 (DIN, CLK, CS)
LedControl lc = LedControl(12, 11, 10, 1);  // Set pins for MAX7219 (DIN=12, CLK=11, CS=10)

// Variables for the rest of the logic
float sinVal;
int toneVal;
unsigned long tepTimer;

void setup() {
    // Initialize the LED matrix
    lc.shutdown(0, false);  // Wake up LED matrix
    lc.setIntensity(0, 8);  // Set brightness (0-15)
    lc.clearDisplay(0);     // Clear the display

    pinMode(8, OUTPUT);     // Buzzer pin
    Serial.begin(9600);     // Start serial communication
}

void displayNumber(int num) {
    // Clear the matrix before displaying a new number
    lc.clearDisplay(0);

    // Display the number on the LED matrix
    switch (num) {
        case 0:
            // Display '0'
            lc.setRow(0, 0, B00111100);
            lc.setRow(0, 1, B01100110);
            lc.setRow(0, 2, B01100110);
            lc.setRow(0, 3, B01100110);
            lc.setRow(0, 4, B01100110);
            lc.setRow(0, 5, B01100110);
            lc.setRow(0, 6, B00111100);
            lc.setRow(0, 7, B00000000);
            break;
        case 1:
            // Display '1'
            lc.setRow(0, 0, B00011000);
            lc.setRow(0, 1, B00111000);
            lc.setRow(0, 2, B00011000);
            lc.setRow(0, 3, B00011000);
            lc.setRow(0, 4, B00011000);
            lc.setRow(0, 5, B00011000);
            lc.setRow(0, 6, B00111110);
            lc.setRow(0, 7, B00000000);
            break;
        case 2:
            // Display '2'
            lc.setRow(0, 0, B00111100);
            lc.setRow(0, 1, B01100110);
            lc.setRow(0, 2, B00000110);
            lc.setRow(0, 3, B00001100);
            lc.setRow(0, 4, B00110000);
            lc.setRow(0, 5, B01100000);
            lc.setRow(0, 6, B01111110);
            lc.setRow(0, 7, B00000000);
            break;
        case 3:
            // Display '3'
            lc.setRow(0, 0, B00111100);
            lc.setRow(0, 1, B01100110);
            lc.setRow(0, 2, B00000110);
            lc.setRow(0, 3, B00011100);
            lc.setRow(0, 4, B00000110);
            lc.setRow(0, 5, B01100110);
            lc.setRow(0, 6, B00111100);
            lc.setRow(0, 7, B00000000);
            break;
    }
}

void loop() {
    int val;
    double data;

    // Read analog value from temperature sensor
    val = analogRead(0);

    // Correct temperature conversion formula
    data = (double)val * (5.0 / 10.24);  // Convert voltage to temperature in degrees Celsius

    // Check the temperature range and display corresponding number on the LED matrix
    if (data < 0) {
        displayNumber(0);  // Display 0
    } else if (data >= 1 && data <= 10) {
        displayNumber(1);  // Display 1
    } else if (data >= 11 && data <= 25) {
        displayNumber(2);  // Display 2
    } else if (data > 25) {
        displayNumber(3);  // Display 3
    }

    // If the temperature exceeds 27°C, sound the buzzer
    if (data > 27) {
        // Generate a sound based on a sine wave
        for (int x = 0; x < 180; x++) {
            sinVal = sin(x * (3.1412 / 180));       // Generate sine wave value
            toneVal = 2000 + (int(sinVal * 1000));  // Calculate tone frequency
            tone(8, toneVal);                        // Play the tone on buzzer
            delay(2);                                // Short delay to modulate the sound
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
