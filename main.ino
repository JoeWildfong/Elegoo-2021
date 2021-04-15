#include "lib/DriverStation.h"
#include "lib/elegoo-car.h"

#include "include/drivebase.hpp"
#include "include/tasks.hpp"

ElegooCar joebot;
DriverStation ds;

static constexpr uint8_t deadzone = 16;

bool testFunc(unsigned long startTime) {
    unsigned long runtime = millis() - startTime;
    if (runtime < 700) {
        Serial.println("Forwards");
        Drivebase::ArcadeDrive(254, 254);
    } else {
        Serial.println("Backwards");
        Drivebase::ArcadeDrive(-254, -254);
    }
    return false;
}

void setup() {
    Serial.begin(115200);
    Drivebase::init(&joebot);
    Drivebase::setDeadzone(deadzone);
}

void autonomous() {}

void teleop() {}

void loop() {
    // Update the Elegoo Car state
    int res = joebot.u16Update();

    Drivebase::ArcadeDrive(ds.getLY(), ds.getLX());

    // update the DriverStation class - this will check if there is new data
    // from the DriverStation application. ds.bUpdate() returns true if new data
    // has been received (10 times/second)
    if (ds.bUpdate()) {
        // now, handle the driver station data depending on what game state we
        // are in
        switch (ds.getGameState()) {
        case ePreGame:
        case ePostGame:
            // During Pre and Post game, the Elegoo should not move!
            joebot.setSpeed(0, 0);
            break;
        case eAutonomous:
            // Handle Autonomous mode
            autonomous();
            break;
        case eTeleop:
            // Handle telop mode
            teleop();
            break;
        }
    }

    Tasks::run();
}