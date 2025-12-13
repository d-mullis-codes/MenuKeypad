/*
 * -----------------------------------------------------------------------------
 * MenuKeypad Library Source File (Simplified Logic)
 * -----------------------------------------------------------------------------
 * Version: 1.1.2
 * -----------------------------------------------------------------------------
 */

#include "MenuKeypad.h"

// Define the indices for the internal tracking arrays
#define UP_INDEX      0
#define DOWN_INDEX    1
#define LEFT_INDEX    2
#define RIGHT_INDEX   3
#define SELECT_INDEX  4

/**
 * @brief Constructor
 */
MenuKeypad::MenuKeypad(uint8_t upPin, uint8_t downPin, uint8_t leftPin, uint8_t rightPin, uint8_t selectPin, unsigned long debounceDelayMillis)
    : _upPin(upPin), _downPin(downPin), _leftPin(leftPin), _rightPin(rightPin), _selectPin(selectPin), _debounceDelay(debounceDelayMillis) {
    
    // Initialize state tracking arrays (Active LOW logic: Released = HIGH)
    for (int i = 0; i < 5; i++) {
        _lastChangeTime[i] = 0;
        _buttonState[i] = HIGH; // Start in the released state (HIGH)
        _lastReading[i] = HIGH; // Start in the released state (HIGH)
    }
}

/**
 * @brief Initializes the keypad pins.
 */
void MenuKeypad::begin() {
    pinMode(_upPin, INPUT);
    pinMode(_downPin, INPUT);
    pinMode(_leftPin, INPUT);
    pinMode(_rightPin, INPUT);
    pinMode(_selectPin, INPUT);
}

/**
 * @brief Helper function to check the state of a single pin using single-shot debouncing.
 * @details This function implements single-shot (press-only) logic.
 */
KeyPress MenuKeypad::checkPin(uint8_t pin, uint8_t keyIndex, KeyPress key) {
    int reading = digitalRead(pin);
    KeyPress returnKey = KEY_NONE;
    
    // 1. Check for change in instantaneous reading
    if (reading != _lastReading[keyIndex]) {
        // Reset the timer if the state is unstable
        _lastChangeTime[keyIndex] = millis();
    }

    // 2. If the time since the last change exceeds the debounce delay
    if ((millis() - _lastChangeTime[keyIndex]) > _debounceDelay) {
        
        // 3. If the button has stabilized into a different state
        if (reading != _buttonState[keyIndex]) {
            _buttonState[keyIndex] = reading; // Update the stable state

            // 4. Check if the new stable state is "PRESSED" (LOW)
            if (_buttonState[keyIndex] == LOW) {
                // This transition from HIGH to LOW is the single-shot press event
                returnKey = key;
            }
        }
    }

    // 5. Save the instantaneous reading for the next loop's instability check
    _lastReading[keyIndex] = reading;
    
    return returnKey;
}

/**
 * @brief Reads the state of the keypad and returns the last detected key press.
 */
KeyPress MenuKeypad::readKey() {
    // Check keys in a typical priority order
    KeyPress currentKey = KEY_NONE;

    currentKey = checkPin(_selectPin, SELECT_INDEX, KEY_SELECT);
    if (currentKey != KEY_NONE) return currentKey;

    currentKey = checkPin(_upPin, UP_INDEX, KEY_UP);
    if (currentKey != KEY_NONE) return currentKey;

    currentKey = checkPin(_downPin, DOWN_INDEX, KEY_DOWN);
    if (currentKey != KEY_NONE) return currentKey;

    currentKey = checkPin(_leftPin, LEFT_INDEX, KEY_LEFT);
    if (currentKey != KEY_NONE) return currentKey;

    currentKey = checkPin(_rightPin, RIGHT_INDEX, KEY_RIGHT);
    if (currentKey != KEY_NONE) return currentKey;

    return KEY_NONE;
}
