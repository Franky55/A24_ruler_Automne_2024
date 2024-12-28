#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "esp_log.h"
#include "TimeBased.h"
#include "I2C_Controller.h"
#include "IMU.h"
#include "IMU_Processus.h"
#include "TCA9534.h"
#include "IO_Expender.h"
#include "Button_Processus.h"
#include "WebBrowser.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// #include "platform.h"
#include "vl53l5cx_api.h"
#include "vl53l5cx_plugin_xtalk.h"

//Global variables
extern TimeBased timer;

//Global Functions
void DoNothing();

#endif



//vl53l5cx_set_i2c_address