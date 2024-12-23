#ifndef TIMEBASED_H
#define TIMEBASED_H

#include <stdio.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_MAX 10
#define TIMER_COOLDOWN_US 1000

class TimeBased {
public:
    // Constructor
    TimeBased();

    // Public methods
    
    void addTask(void (*function)(void));


private:
    // Member variables
    void (*tasks[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_MAX])(void);
    int numTasks;

    void manageTasks();
    void initializeTimer();
    // Timer handle
    esp_timer_handle_t timerHandler;
};

#endif // TIMEBASED_H
