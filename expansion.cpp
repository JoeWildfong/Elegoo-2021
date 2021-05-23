#include "include/expansion.hpp"
#include <Wire.h>

void Expansion::init() { Wire.begin(); }

void Expansion::pinMode(uint8_t pin, uint8_t mode) {
    if (mode == INPUT) {
        Expansion::writePin(pin, HIGH);
    } else if (mode == OUTPUT) {
        Expansion::writePin(pin, LOW);
    }
}

int Expansion::writePin(uint8_t pin, bool value) {
    bitWrite(pinStates, pin, value);
    return updateHardware();
}

bool Expansion::readPin(uint8_t pin) {
    uint8_t read;
    while (Wire.available()) {
        read = Wire.read();
    }
    return bitRead(read, pin);
}

int Expansion::updateHardware() {
    Wire.beginTransmission(ADDRESS);
    Wire.write(pinStates);
    return Wire.endTransmission();
}