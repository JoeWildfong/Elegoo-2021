#pragma once

#include "Arduino.h"

static constexpr unsigned int numSlots = 10;

namespace Tasks {
/// \brief Class representing a task to be executed repeatedly for a duration.
///
/// Task will be run until the function returns true, or for a specified
/// duration, whichever comes first.
class Task {
    bool (*fn)(unsigned long);
    void (*end)();
    unsigned long startTime;
    unsigned long duration;

  public:
    /// Creates a task that will execute until fn returns true, or duration
    /// milliseconds have passed, whichever comes first.
    ///
    /// @param fn Function to be executed. If it returns true, the task will
    /// stop running.
    /// @param duration Max time to run the task for. Set to 0 or omit for no
    /// timeout.
    /// @param end Function that will be executed when task ends.
    Task(bool (*fn)(unsigned long), unsigned long duration = 0,
         void (*end)() = NULL)
        : fn(fn), duration(duration), end(end){};

    /// Copy-constructs a Task
    Task(const Task &t) = default;
    Task operator=(const Task &t);

    /// Move-constructs a Task
    Task(Task &&t) = default;
    Task operator=(Task &&t);

    /// Empty Task constructor, used for initialization
    Task() : fn(NULL), duration(0), end(NULL){};

    /// Schedules this task for repeated execution
    bool schedule();

    /// Runs this task, returning true if one of the end conditions is met (i.e.
    /// fn returns true or duration milliseconds have passed)
    bool run();

    /// NULLs out fn, used to deschedule the task when it's done
    void done();
};

/// Schedules a Task for repeated execution
bool schedule(Task &task);

/// Schedules a Task for repeated execution
bool schedule(const Task &task);

/// Creates and schedules a Task for repeated execution
bool schedule(bool (*fn)(unsigned long), unsigned long duration = 0,
              void (*end)() = NULL);

/// Runs all tasks currently scheduled, and removes them if one of the end
/// conditions is met (i.e. duration has passed or function returns true)
void run();

namespace {
    // private declarations
    Task taskSlots[numSlots];
} // namespace

} // namespace Tasks