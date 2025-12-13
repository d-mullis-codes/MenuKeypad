# MenuKeypad Library

A simple, robust library for interfacing with a 5-key directional menu keypad (Up, Down, Left, Right, Select) on Arduino-compatible boards.

## 📌 Features

* **5-Key Support:** Up, Down, Left, Right, Select.
* **Active LOW Logic:** Designed for keypads using external pull-up resistors (pin is LOW when pressed).
* **Software Debouncing:** Implements non-blocking debouncing logic for reliable key press detection.
* **Simple Interface:** Easy-to-use `readKey()` function.

## 🛠️ Hardware Setup (Arduino Nano)

The library is designed for the following pinout:

| Function | Arduino Pin |
| :--- | :--- |
| **Key Up** | D5 |
| **Key Down** | D4 |
| **Key Left** | D3 |
| **Key Right** | D7 |
| **Key Select** | D6 |

**Wiring:**

1.  Connect one side of each momentary button to the specified digital pin.
2.  Connect the other side of each momentary button to **GND**.
3.  Connect an external pull-up resistor (e.g., $10\text{k}\Omega$) from each digital pin to **VCC** ($5\text{V}$).

## 🚀 Usage

### Installation

1.  Download the repository.
2.  Rename the main folder to `MenuKeypad`.
3.  Place the `MenuKeypad` folder into your Arduino Sketchbook's `libraries` folder.

### Example

```cpp
#include <MenuKeypad.h>

// Define the pins 
#define UP_KEY_PIN      5  // D5
// ... other pin definitions

MenuKeypad keypad(UP_KEY_PIN, DOWN_KEY_PIN, LEFT_KEY_PIN, RIGHT_KEY_PIN, SELECT_KEY_PIN);

void setup() {
  Serial.begin(9600);
  keypad.begin(); // Initialize pins
}

void loop() {
  KeyPress key = keypad.readKey();

  if (key != KEY_NONE) {
    // Handle the key press event here
    switch (key) {
      case KEY_UP: /* ... */ break;
      case KEY_SELECT: /* ... */ break;
      // ... other cases
    }
  }
}
