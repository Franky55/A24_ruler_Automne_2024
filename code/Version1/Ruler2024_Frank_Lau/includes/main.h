#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "esp_log.h"
#include "TimeBased.h"
#include "I2C_Controller.h"
#include "IMU.h"
#include "IMU_Processus.h"
#include "TCA9534.h"

//Global variables
extern IMU imu;
extern TimeBased timer;

//Global Functions
void DoNothing();

#endif