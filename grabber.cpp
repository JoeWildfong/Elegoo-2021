#include "include/grabber.hpp"

#include <Servo.h>

static constexpr uint8_t grabberServoPin = 6;

static uint8_t servoAngle = 0;

static Servo grabberServo;

static uint8_t clampRange(uint8_t input) {
    // clamps a uint8_t to 0 - 180 range
    return input < 0 ? 0 : input > 180 ? 180 : input;
}

void Grabber::init() { grabberServo.attach(grabberServoPin); }

void Grabber::setAngle(uint8_t degrees) {
    servoAngle = clampRange(degrees);
    grabberServo.write(servoAngle);
}

void Grabber::changeAngle(int16_t degrees) {
    if (degrees == 0) {
        return;
    }
    servoAngle = clampRange(servoAngle + degrees);
    grabberServo.write(servoAngle);
}

void Grabber::moveUp(uint8_t degrees) {
    if (degrees == 0) {
        return;
    }
    servoAngle = clampRange(servoAngle + degrees);
    grabberServo.write(servoAngle);
}

void Grabber::moveDown(uint8_t degrees) {
    if (degrees == 0) {
        return;
    }
    servoAngle = clampRange(servoAngle - degrees);
    grabberServo.write(servoAngle);
}