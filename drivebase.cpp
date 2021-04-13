#include "include/drivebase.hpp"

void Drivebase::init() {
    pinMode(Drivebase::LEFT_SPEED_PIN, OUTPUT);
    pinMode(Drivebase::RIGHT_SPEED_PIN, OUTPUT);
    pinMode(Drivebase::LEFT_FORWARD_PIN, OUTPUT);
    pinMode(Drivebase::LEFT_BACKWARD_PIN, OUTPUT);
    pinMode(Drivebase::RIGHT_FORWARD_PIN, OUTPUT);
    pinMode(Drivebase::RIGHT_BACKWARD_PIN, OUTPUT);
    digitalWrite(LEFT_SPEED_PIN, HIGH);
    digitalWrite(RIGHT_SPEED_PIN, HIGH);
}

void Drivebase::drive(double left, double right) {
    analogWrite(Drivebase::LEFT_SPEED_PIN, round(abs(left) * 1023));
    analogWrite(Drivebase::RIGHT_SPEED_PIN, round(abs(right) * 1023));

    if (left == 0) {
        digitalWrite(Drivebase::LEFT_FORWARD_PIN, LOW);
        digitalWrite(Drivebase::LEFT_BACKWARD_PIN, LOW);
    } else if (left < 0) {
        digitalWrite(Drivebase::LEFT_FORWARD_PIN, LOW);
        digitalWrite(Drivebase::LEFT_BACKWARD_PIN, HIGH);
    } else {
        digitalWrite(Drivebase::LEFT_FORWARD_PIN, HIGH);
        digitalWrite(Drivebase::LEFT_BACKWARD_PIN, LOW);
    }

    if (right == 0) {
        digitalWrite(Drivebase::RIGHT_FORWARD_PIN, LOW);
        digitalWrite(Drivebase::RIGHT_BACKWARD_PIN, LOW);
    } else if (right < 0) {
        digitalWrite(Drivebase::RIGHT_FORWARD_PIN, LOW);
        digitalWrite(Drivebase::RIGHT_BACKWARD_PIN, HIGH);
    } else {
        digitalWrite(Drivebase::RIGHT_FORWARD_PIN, HIGH);
        digitalWrite(Drivebase::RIGHT_BACKWARD_PIN, LOW);
    }
}

void Drivebase::stop() {
    Drivebase::drive(0, 0);
}