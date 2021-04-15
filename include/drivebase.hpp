#pragma once

#include "../lib/elegoo-car.h"

/// Namespace containing functions to control drive motors.
namespace Drivebase {

/// Initializes pin modes and sets speeds to full
void init(ElegooCar *car);

/// Sets the deadzone for the drivebase.
void setDeadzone(uint8_t deadzone);

/// Sets motor speed and direction to given values between -1 and 1.
/// Negative values move backwards.
/// Robot will keep moving - it will not automatically stop.
void TankDrive(int16_t left, int16_t right);

/// Sets motors based on x and y coordinates.
/// Positive y is forwards, positive x is a right turn.
/// Robot will not automatically stop.
void ArcadeDrive(int16_t y, int16_t x);

/// Stops the robot. Equivalent to TankDrive(0, 0) or ArcadeDrive(0, 0).
void stop();

namespace {
    // private definitions
    ElegooCar *m_car;
    uint8_t m_deadzone = 0;
} // namespace

} // namespace Drivebase