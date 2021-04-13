#include "include/drivebase.hpp"
#include "include/tasks.hpp"

bool testFunc(unsigned long startTime) {
    unsigned long runtime = millis() - startTime;
    if (runtime < 700) {
        Serial.println("Forwards");
        Drivebase::drive(1, 1);
    } else {
        Serial.println("Backwards");
        Drivebase::drive(-1, -1);
    }
    return false;
}

void setup() {
    Serial.begin(9600);
    Drivebase::init();
    using Tasks::Task;
    Task test {testFunc, 1000, Drivebase::stop};
    if (!test.schedule()) {
        Serial.println("Failed to schedule");
    }
    Serial.println("Hello World");
}

void loop() {
    Tasks::run();
}