#include "include/drivebase.hpp"

static double copySign(double dest, double source) {
    return source >= 0 ? dest : -dest;
}

static double clamp(double in, double min, double max) {
    return in < min ? min : in > max ? max : in;
}

static void setPower(double left, double right) {
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

void Drivebase::TankDrive(double left, double right) {
    left = clamp(left, -1, 1);
    right = clamp(right, -1, 1);
    setPower(left, right);
}

void Drivebase::ArcadeDrive(double y, double x) {
    double left, right;

    double maxInput = copySign(max(abs(y), abs(x)), y);

    if (y >= 0.0) {
        // First quadrant, else second quadrant
        if (x >= 0.0) {
            left = maxInput;
            right = y - x;
        } else {
            left = y + x;
            right = maxInput;
        }
    } else {
        // Third quadrant, else fourth quadrant
        if (x >= 0.0) {
            left = y + x;
            right = maxInput;
        } else {
            left = maxInput;
            right = y - x;
        }
    }

    left = clamp(left, -1, 1);
    right = clamp(right, -1, 1);
    setPower(left, right);
}

void Drivebase::stop() { Drivebase::TankDrive(0, 0); }