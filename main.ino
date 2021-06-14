#include "lib/DriverStation.h"

#include "include/drivebase.hpp"
#include "include/encoders.hpp"
#include "include/grabber.hpp"
#include "include/tasks.hpp"

static ElegooCar *joebot = new ElegooCar();
static DriverStation *ds = new DriverStation();

static constexpr uint8_t DRIVEBASE_DEADZONE = 32;

static constexpr uint8_t GRABBER_DEADZONE = 5;
static constexpr float GRABBER_COEFFICIENT = 0.1;

void setup() {
    Serial.begin(115200);

    Drivebase::init(joebot);
    Drivebase::setDeadzone(DRIVEBASE_DEADZONE);

    Encoders::init();

    Grabber::init();
    Grabber::setDeadzone(GRABBER_DEADZONE);
}

static void autonomous() {}

static void teleop() {
    Drivebase::arcadeDrive(ds->getLY(), ds->getLX());
    
    int16_t triggerDiff = (int16_t)ds->getLTrig() - (int16_t)ds->getRTrig();
    Grabber::changeAngle(triggerDiff * GRABBER_COEFFICIENT);
}

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

    Grabber::update();

    Tasks::run();
}