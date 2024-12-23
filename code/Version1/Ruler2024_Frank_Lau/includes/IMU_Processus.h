#ifndef IMU_PROCESSUS_H
#define IMU_PROCESSUS_H

#include "main.h"
#include "esp_log.h"

//Global variables
extern void (*IMU_function)(void);

//Functions
void InitializeIMUProcessus();
void GetAllAxes();

#endif