/*
 * -----------------------------------------------------------------------------
 * MenuKeypad Library
 * -----------------------------------------------------------------------------
 * Version: 1.1.2 (Simplified & Corrected Single-Shot Logic)
 * -----------------------------------------------------------------------------
 */

#ifndef MENUKEYPAD_H
#define MENUKEYPAD_H

#include <Arduino.h>

enum KeyPress {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SELECT
};

class MenuKeypad {
public:
    // ... (Constructor signature remains the same)
    MenuKeypad(uint8_t upPin, uint8_t downPin, uint8_t leftPin, uint8_t rightPin, uint8_t selectPin, unsigned long debounceDelayMillis = 50);

    void begin();

    KeyPress readKey();

private:
    uint8_t _upPin, _downPin, _leftPin, _rightPin, _selectPin;
    unsigned long _debounceDelay;
    
    // Arrays for robust single-shot reading
    unsigned long _lastChangeTime[5]; // Stores the time of the last pin change
    int _buttonState[5];             // The currently debounced, stable state (LOW/HIGH)
    int _lastReading[5];             // The instantaneous reading from the previous loop iteration
    
    /**
     * @brief Helper function to check the state of a single pin using single-shot debouncing.
     */
    KeyPress checkPin(uint8_t pin, uint8_t keyIndex, KeyPress key);
};

#endif // MENUKEYPAD_H
