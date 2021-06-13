#pragma once

#include <Arduino.h>

namespace Grabber {

void init();

void setDeadzone(uint8_t deadzone);

void setAngle(uint8_t degrees);

void changeAngle(int16_t degrees);

void moveUp(uint8_t degrees);

void moveDown(uint8_t degrees);

} // namespace Grabber