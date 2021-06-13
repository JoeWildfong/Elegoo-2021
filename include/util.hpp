#pragma once

#include <Arduino.h>

namespace Util {

inline int16_t copySign(int16_t dest, int16_t source) {
    return source >= 0 ? dest : -dest;
}

inline uint8_t deadzone_8(uint8_t val, uint8_t deadzone) {
    return val < deadzone ? 0 : val;
}

inline int16_t deadzone_16(int16_t val, uint8_t deadzone) {
    return abs(val) < deadzone ? 0 : val;
}

inline uint8_t clamp_8(uint8_t input, uint8_t min, uint8_t max) {
    return input < min ? min : input > max ? max : input;
}

inline int16_t clamp_16(int16_t input, int16_t min, int16_t max) {
    return input < min ? min : input > max ? max : input;
}

} // namespace Util