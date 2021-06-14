#include "include/grabber.hpp"
#include "include/util.hpp"

#include <Servo.h>

static constexpr uint8_t GRABBER_SERVO_PIN = 3;

static constexpr uint8_t MIN_ANGLE = 60;
static constexpr uint8_t MAX_ANGLE = 160;

static Servo grabberServo;

static uint8_t grabberServoDeadzone = 0;
static uint8_t grabberServoAngle = MIN_ANGLE;

static inline uint8_t grabberClamp8(uint8_t angle) {
    return Util::clamp_8(angle, MIN_ANGLE, MAX_ANGLE);
}

static inline int16_t grabberClamp16(int16_t angle) {
    return Util::clamp_16(angle, MIN_ANGLE, MAX_ANGLE);
}

void Grabber::init() {
    grabberServo.attach(GRABBER_SERVO_PIN);
    grabberServo.write(grabberServoAngle);
}

void Grabber::setDeadzone(uint8_t deadzone) { grabberServoDeadzone = deadzone; }

void Grabber::setAngle(uint8_t degrees) {
    grabberServoAngle = grabberClamp8(degrees);
    grabberServo.write(grabberServoAngle);
}

void Grabber::changeAngle(int16_t degrees) {
    if (abs(degrees) < grabberServoDeadzone) {
        return;
    }
    grabberServoAngle = grabberClamp16(grabberServoAngle + degrees);
    grabberServo.write(grabberServoAngle);
}

void Grabber::moveUp(uint8_t degrees) {
    if (degrees < grabberServoDeadzone) {
        return;
    }
    grabberServoAngle = grabberClamp16(grabberServoAngle + degrees);
    grabberServo.write(grabberServoAngle);
}

void Grabber::moveDown(uint8_t degrees) {
    if (degrees < grabberServoDeadzone) {
        return;
    }
    grabberServoAngle = grabberClamp16(grabberServoAngle - degrees);
    grabberServo.write(grabberServoAngle);
}
