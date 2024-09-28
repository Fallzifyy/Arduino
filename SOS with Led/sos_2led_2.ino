int ledPin1 = 10;
int ledPin2 = 11;

void setup() {
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
}

// Function to blink a dot (short blink) on a specified pin
void blinkDot(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(100);
}

// Function to blink a dash (long blink) on a specified pin
void blinkDash(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(100);
}

void blinkSOS(int ledPin) {
    // S(...) - three dots
    for (int x = 0; x < 3; x++) {
        blinkDot(ledPin);
    }
    delay(100);

    // O(---) - three dashes
    for (int x = 0; x < 3; x++) {
        blinkDash(ledPin);
    }
    delay(100);

    // S(...) - three dots
    for (int x = 0; x < 3; x++) {
        blinkDot(ledPin);
    }
}

void loop() {
    // Blink SOS on the first LED
    blinkSOS(ledPin1);

    // Pause between SOS signals
    delay(1000);

    // Blink SOS on the second LED
    blinkSOS(ledPin2);

    // Pause before repeating the alternate SOS pattern
    delay(5000);
}
