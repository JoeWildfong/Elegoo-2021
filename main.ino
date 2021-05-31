#include "lib/DriverStation.h"

#include "include/drivebase.hpp"
#include "include/tasks.hpp"

static ElegooCar *joebot = new ElegooCar();
static DriverStation *ds = new DriverStation();

static constexpr uint8_t deadzone = 32;

void setup() {
    Serial.begin(115200);
    Drivebase::init(joebot);
    Drivebase::setDeadzone(deadzone);
}

static void autonomous() {}

static void teleop() { Drivebase::arcadeDrive(ds->getLY(), ds->getLX()); }

void loop() {
    // update the DriverStation class - this will check if there is new data
    // from the DriverStation application. ds.bUpdate() returns true if new data
    // has been received (10 times/second)
    if (ds->bUpdate()) {
        // now, handle the driver station data depending on what game state we
        // are in
        switch (ds->getGameState()) {
        case ePreGame:
        case ePostGame:
            // During Pre and Post game, the Elegoo should not move!
            Drivebase::stop();
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