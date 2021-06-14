#include "include/tasks.hpp"

Tasks::Task Tasks::Task::operator=(const Tasks::Task &t) {
    return Tasks::Task(t);
}

Tasks::Task Tasks::Task::operator=(Tasks::Task &&t) { return Tasks::Task(t); }

bool Tasks::Task::schedule() {
    Serial.println("Scheduling task...");
    for (int i = 0; i < numSlots; i++) {
        if (taskSlots[i].fn == NULL) {
            this->startTime = millis();
            taskSlots[i].fn = this->fn;
            taskSlots[i].end = this->end;
            taskSlots[i].duration = this->duration;
            taskSlots[i].startTime = this->startTime;
            Serial.print("Scheduled in slot ");
            Serial.println(i);
            return true;
        }
    }
    return false;
}

bool Tasks::Task::run() {
    if (this->fn == NULL) {
        return false;
    }
    if (this->duration != 0 && this->duration < millis() - this->startTime) {
        return true;
    }
    return this->fn(this->startTime);
}

void Tasks::Task::done() {
    if (this->end != NULL) {
        this->end();
    }
    fn = NULL;
}

bool Tasks::schedule(Task &task) { return task.schedule(); }

bool Tasks::schedule(bool (*fn)(unsigned long), unsigned long duration,
                     void (*end)()) {
    return Task(fn, duration, end).schedule();
}

void Tasks::run() {
    for (int i = 0; i < numSlots; i++) {
        if (taskSlots[i].run()) {
            Serial.print("Descheduling task ");
            Serial.println(i);
            taskSlots[i].done();
        }
    }
}