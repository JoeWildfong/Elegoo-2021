#pragma once

#include <Arduino.h>

namespace Expansion {
// I2C address of expansion board
constexpr int ADDRESS = 0x20;

// status codes returned on write
constexpr int SUCCESS = 0;
constexpr int DATA_TOO_LONG = 1;
constexpr int ADDRESS_TRANSMIT_ERROR = 2;
constexpr int DATA_TRANSMIT_ERROR = 3;
constexpr int OTHER_ERROR = 4;

/// Initializes the wire interface to communicate with the expansion board.
void init();

/// Sets up a pin on the expansion board for a given I/O mode.
/// @param pin The pin to act on, from 0 to 7.
/// @param mode The input mode for the pin. 
/// Currently only INPUT and OUTPUT do anything.
void pinMode(uint8_t pin, uint8_t mode);

/// Writes a value to a pin on the expansion board.
/// @param pin The pin to write to, from 0 to 7.
/// @param value The value to write to the pin, either LOW or HIGH.
/// @return A status code indicating the status of the transmission.
int writePin(uint8_t pin, bool value);

/// Reads the value of a pin on the expansion board. 
/// The pin must be set to the INPUT pinMode or written HIGH first.
/// @param pin The pin to read, from 0 to 7.
/// @return The state of the pin being read.
bool readPin(uint8_t pin);

/// Sends pin states to the expansion board over I2C. 
/// Called automatically when a pin is written. 
/// @return A status code indicating the status of the transmission.
int updateHardware();

namespace {
    // private stuff
    uint8_t pinStates = 0;
} // namespace

} // namespace Expansion