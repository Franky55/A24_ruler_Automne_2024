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

//Global variables
extern TimeBased timer;

//Global Functions
void DoNothing();

#endif