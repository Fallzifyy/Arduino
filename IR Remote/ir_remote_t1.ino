void setup() {
#include <IRremote.h>  // Include the IRremote library

int RECV_PIN = 11;  // Set the IR receiver pin to 11
IRrecv irrecv(RECV_PIN);  // Create an IR receiver object
decode_results results;  // Create a variable to store IR decoding results
int currentNumber = 0;  // Variable to keep track of the current number

// Array to store IR codes from the remote
long codes[12] = {
    0xFD30CF, 0xFD08F7,  // 0, 1
    0xFD8877, 0xFD48B7,  // 2, 3
    0xFD28D7, 0xFDA857,  // 4, 5
    0xFD6897, 0xFD18E7,  // 6, 7
    0xFD9867, 0xFD58A7,  // 8, 9
    0xFD20DF, 0xFD609F   // +, -
};

// Array to define the LED patterns for numbers 0-9
int number[10][8] = {
    {0, 0, 0, 1, 0, 0, 0, 1}, // 0
    {0, 1, 1, 1, 1, 1, 0, 1}, // 1
    {0, 0, 1, 0, 0, 0, 1, 1}, // 2
    {0, 0, 1, 0, 1, 0, 0, 1}, // 3
    {0, 1, 0, 0, 1, 1, 0, 1}, // 4
    {1, 0, 0, 0, 1, 0, 0, 1}, // 5
    {1, 0, 0, 0, 0, 0, 0, 1}, // 6
    {0, 0, 1, 1, 1, 1, 0, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0, 1}, // 8
    {0, 0, 0, 0, 1, 1, 0, 1}  // 9
};

// Function to display numbers on the LED module
void numberShow(int i) {
    for (int pin = 2; pin <= 9; pin++) {
        digitalWrite(pin, number[i][pin - 2]);
    }
}

void setup() {
    Serial.begin(9600);  // Initialize serial communication at 9600 baud
    irrecv.enableIRIn();  // Start the IR receiver

    // Set pins 2 through 9 as OUTPUT
    for (int pin = 2; pin <= 9; pin++) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);  // Turn off LEDs initially
    }
}

void loop() {
    if (irrecv.decode(&results)) {  // Check if IR signal is received
        Serial.print("Received code: ");
        Serial.println(results.value, HEX);  // Print the received IR code

        for (int i = 0; i < 12; i++) {
            if (results.value == codes[i]) {
                if (i <= 9) {  // Handle numbers 0-9
                    numberShow(i);  // Display the corresponding number
                    currentNumber = i;
                    Serial.print("Current Number: ");
                    Serial.println(i);
                } else if (i == 10 && currentNumber != 0) {  // Handle decrement
                    currentNumber--;
                    numberShow(currentNumber);
                    Serial.print("Decreased to: ");
                    Serial.println(currentNumber);
                } else if (i == 11 && currentNumber != 9) {  // Handle increment
                    currentNumber++;
                    numberShow(currentNumber);
                    Serial.print("Increased to: ");
                    Serial.println(currentNumber);
                }
                break;
            }
        }
        irrecv.resume();  // Receive the next value
    }
}
