#include "TimeBased.h"

TimeBased::TimeBased() {
    numTasks = 0;

    for (int i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_MAX; i++)
    {
        tasks[i] = nullptr;
    }

    initializeTimer();
}

void TimeBased::addTask(void (*function)(void))
{
    tasks[numTasks] = function;
    numTasks++;
}

// Private method: Manage tasks
void TimeBased::manageTasks() {
    for (unsigned char i = 0; i < numTasks; i++) {
        if (tasks[i]) {
            tasks[i]();
        }
    }
}

// Public method: Initialize and start the timer
void TimeBased::initializeTimer() {
    // Lambda function to invoke the class member function
    auto callbackLambda = [](void* arg) {
        // Cast the void* arg to TimeBased*
        TimeBased* instance = static_cast<TimeBased*>(arg);
        // Call the non-static member function
        instance->manageTasks();
    };

    // Timer arguments with all fields explicitly initialized
    const esp_timer_create_args_t my_timer_args = {
        .callback = callbackLambda,       // Set the lambda as callback
        .arg = this,                      // Pass the current instance as context
        .dispatch_method = ESP_TIMER_TASK,
        .name = "TimeBasedService",
        .skip_unhandled_events = false    // Explicitly initialize this field
    };

    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timerHandler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timerHandler, TIMER_COOLDOWN_US));
}
