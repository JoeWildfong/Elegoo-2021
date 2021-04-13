#pragma once

/// Namespace containing functions to control drive motors.
namespace Drivebase {
const int LEFT_SPEED_PIN = 5;
const int RIGHT_SPEED_PIN = 6;
const int LEFT_FORWARD_PIN = 7;
const int LEFT_BACKWARD_PIN = 8;
const int RIGHT_BACKWARD_PIN = 9;
const int RIGHT_FORWARD_PIN = 11;

/// Initializes pin modes and sets speeds to full
void init();

/// Sets motor speed and direction to given values between -1 and 1.
/// Negative values move backwards.
/// Robot will keep moving - it will not automatically stop.
void drive(double left, double right);

/// Stops the robot. Equivalent to drive(0, 0).
void stop();

namespace {
    // private definitions
}

} // namespace Drivebase