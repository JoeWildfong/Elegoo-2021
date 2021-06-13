#include "include/grabber.hpp"
#include "include/util.hpp"

#include <Servo.h>

static constexpr uint8_t grabberServoPin = 3;

static uint8_t servoDeadzone = 0;
static uint8_t servoAngle = 0;

static Servo grabberServo;

void Grabber::init() {
    grabberServo.attach(grabberServoPin);
    grabberServo.write(servoAngle);
}

void Grabber::setDeadzone(uint8_t deadzone) { servoDeadzone = deadzone; }

void Grabber::setAngle(uint8_t degrees) {
    servoAngle = Util::clamp_8(degrees, 0, 180);
    grabberServo.write(servoAngle);
}

void Grabber::changeAngle(int16_t degrees) {
    if (degrees < servoDeadzone) {
        return;
    }
    servoAngle = Util::clamp_16(servoAngle + degrees, 0, 180);
    grabberServo.write(servoAngle);
}

void Grabber::moveUp(uint8_t degrees) {
    if (degrees < servoDeadzone) {
        return;
    }
    servoAngle = Util::clamp_16(servoAngle + degrees, 0, 180);
    grabberServo.write(servoAngle);
}

void Grabber::moveDown(uint8_t degrees) {
    if (degrees < servoDeadzone) {
        return;
    }
    servoAngle = Util::clamp_16(servoAngle - degrees, 0, 180);
    grabberServo.write(servoAngle);
}
