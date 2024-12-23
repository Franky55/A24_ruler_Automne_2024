#ifndef IMU_H
#define IMU_H

#include "esp_log.h"
#include "I2C_Controller.h"

class IMU
{
private:
    // I2C_Controller* i2c;
    uint8_t ACCEL_CONFIG0_REG = 0x21;
    uint8_t ACCEL_CONFIG1_REG = 0x24;
    uint8_t PWR_MGMT0_REG = 0x1F;
    uint8_t ACCEL_DATA_REG = 0x0B;
    uint8_t deviceAddress = 0x69;

    icm42670_t dev;
    
    // void WriteRegister(uint8_t reg, uint8_t value);
    // void ReadRegister(uint8_t reg, uint8_t* buffer, size_t size);
public:
    IMU();
    void ReadAllAxes(int16_t* accel_x, int16_t* accel_y, int16_t* accel_z);
    void ReadAxe_X(int16_t *value);
    void ReadAxe_Y(int16_t *value);
    void ReadAxe_Z(int16_t *value);
    void ReadAllGyros(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z);
    void ReadGyro_X(int16_t *value);
    void ReadGyro_Y(int16_t *value);
    void ReadGyro_Z(int16_t *value);
    void Initialize();
};




#endif