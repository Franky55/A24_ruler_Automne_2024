#include "IMU_Processus.h"

void (*IMU_function)(void);
IMU imu;

//State: 0
void InitializeIMUProcessus()
{
    imu.Initialize();
    IMU_function = GetAllAxes;//For reading the data
    //IMU_function = DoNothing;//Do nothing
}


//State: 1
void GetAllAxes()
{
    static long counterAxe = 0;
    counterAxe++;

    if(counterAxe >= 100)//1 fois seconde
    {
        counterAxe =0;
        int16_t axe_X;
        int16_t axe_Y;
        int16_t axe_Z;

        imu.ReadAllAxes(&axe_X, &axe_Y, &axe_Z);
        
        send_sse_update(axe_X, axe_Y, axe_Z);
        ESP_LOGI("IMU", "Accel X: %d, Y: %d, Z: %d", axe_X, axe_Y, axe_Z);
    }
}