#include <MenuKeypad.h>

// Define the pins based on your request (Arduino Nano pin names)
#define UP_KEY_PIN      5  // D5
#define DOWN_KEY_PIN    4  // D4
#define LEFT_KEY_PIN    3  // D3
#define RIGHT_KEY_PIN   7  // D7
#define SELECT_KEY_PIN  6  // D6

// Create an instance of the MenuKeypad class
// The default debounce of 50ms will be used
MenuKeypad keypad(UP_KEY_PIN, DOWN_KEY_PIN, LEFT_KEY_PIN, RIGHT_KEY_PIN, SELECT_KEY_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("--- MenuKeypad Basic Test ---");
  keypad.begin(); // Initialize the keypad pins
}

void loop() {
  // Read the current state of the keypad
  KeyPress currentKey = keypad.readKey();

  // Check if a key was pressed (currentKey will be KEY_NONE if no key is pressed)
  if (currentKey != KEY_NONE) {
    Serial.print("Key Pressed: ");
    
    // Handle the key press
    switch (currentKey) {
      case KEY_UP:
        Serial.println("UP");
        break;
      case KEY_DOWN:
        Serial.println("DOWN");
        break;
      case KEY_LEFT:
        Serial.println("LEFT");
        break;
      case KEY_RIGHT:
        Serial.println("RIGHT");
        break;
      case KEY_SELECT:
        Serial.println("SELECT");
        break;
      default:
        // Should not happen, but good practice
        Serial.println("UNKNOWN");
        break;
    }
  }

  // A small delay to keep the loop from spinning too fast
  delay(10);
}
