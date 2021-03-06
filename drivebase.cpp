#include "include/drivebase.hpp"
#include "include/util.hpp"

static ElegooCar *m_car;
static uint8_t m_deadzone = 0;

void Drivebase::init(ElegooCar *car) { m_car = car; }

void Drivebase::setDeadzone(uint8_t deadzone) { m_deadzone = deadzone; }

void Drivebase::tankDrive(int16_t left, int16_t right) {
    left = Util::deadzone_16(left, m_deadzone);
    right = Util::deadzone_16(right, m_deadzone);
    m_car->setSpeed(left, right);
}

void Drivebase::arcadeDrive(int16_t y, int16_t x) {
    int16_t left, right;

    int16_t maxInput = Util::copySign(max(abs(y), abs(x)), y);

    if (y >= 0) {
        // First quadrant, else second quadrant
        if (x >= 0) {
            left = maxInput;
            right = y - x;
        } else {
            left = y + x;
            right = maxInput;
        }
    } else {
        // Third quadrant, else fourth quadrant
        if (x >= 0) {
            left = y + x;
            right = maxInput;
        } else {
            left = maxInput;
            right = y - x;
        }
    }

    left = Util::deadzone_16(left, m_deadzone);
    right = Util::deadzone_16(right, m_deadzone);
    m_car->setSpeed(left, right);
}

void Drivebase::stop() { m_car->setSpeed(0, 0); }