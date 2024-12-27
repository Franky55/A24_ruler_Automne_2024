#include "IMU_Processus.h"

float mapValue(float x, float in_min, float in_max, float out_min, float out_max);
float reglerZ(float z, float x);
float reglerY(float y, float x);
float calculerAngles_z(float z, float x);
float calculerAngles_y(float y, float x);

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

    if(counterAxe >= 100)//10 fois seconde
    {
        counterAxe =0;
        int16_t axe_X;
        int16_t axe_Y;
        int16_t axe_Z;

        imu.ReadAllAxes(&axe_X, &axe_Y, &axe_Z);

        float angle_y = calculerAngles_y( axe_Y, axe_X );
        float angle_z = calculerAngles_z( axe_Z,  axe_X) ;
        
        send_sse_update(angle_y, angle_z);
        ESP_LOGI("IMU", "Accel X: %d, Y: %d, Z: %d", axe_X, axe_Y, axe_Z);
    }
}


// Fonction pour mapper une valeur d'un intervalle à un autre
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Fonction pour ajuster la valeur de z selon x
float reglerZ(float z, float x) {
    if (x <= 0) {
        return z * -1;
    }
    return z;
}

// Fonction pour ajuster la valeur de y selon x
float reglerY(float y, float x) {
    if (x <= 0) {
        return y * -1;
    }
    return y;
}

// Fonction principale pour calculer les angles
float calculerAngles_y(float y, float x) {
 
    float mapped_y1 = mapValue(y, -2100, 2100, -180, 0);

    mapped_y1 = reglerY(mapped_y1, x);

    return  mapped_y1;
    
}

 float calculerAngles_z(float z, float x) {
 
    float mapped_z1 = mapValue(z, -2100, 2100, -180, 0);

    mapped_z1 = reglerY(mapped_z1, x);

    return mapped_z1;
}
 