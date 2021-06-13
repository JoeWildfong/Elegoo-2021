#pragma once

#include <Arduino.h>

namespace Grabber {

/// Initializes the grabber module
void init();

/// Sets the deadzone for the grabber
void setDeadzone(uint8_t deadzone);

/// Sets an absolute angle for the grabber.
/// Will be clamped to minimum and maximum angles.
void setAngle(uint8_t degrees);

/// Changes the grabber angle.
/// Positive values move up, negative values move down.
/// After calculating the new angle, it will be clamped.
void changeAngle(int16_t degrees);

/// Moves the grabber up. Equivalent to changeAngle with a positive angle.
/// Slightly more optimized.
void moveUp(uint8_t degrees);

/// Moves the grabber down. Equivalent to changeAngle with a negative angle.
/// Slightly more optimized.
void moveDown(uint8_t degrees);

} // namespace Grabber