#include "IMU.h"

IMU::IMU()
{
}

void IMU::Initialize()
{
    dev = { I2C_NUM_0 };
    ESP_ERROR_CHECK(
        icm42670_init_desc(&dev, 0x69, I2C_NUM_0, GPIO_NUM_2, GPIO_NUM_3));
    ESP_ERROR_CHECK(icm42670_init(&dev));

    // enable accelerometer and gyro in low-noise (LN) mode
    ESP_ERROR_CHECK(icm42670_set_gyro_pwr_mode(&dev, ICM42670_GYRO_ENABLE_LN_MODE));
    ESP_ERROR_CHECK(icm42670_set_accel_pwr_mode(&dev, ICM42670_ACCEL_ENABLE_LN_MODE));

    /* OPTIONAL */
    // enable low-pass-filters on accelerometer and gyro
    ESP_ERROR_CHECK(icm42670_set_accel_lpf(&dev, ICM42670_ACCEL_LFP_53HZ));
    ESP_ERROR_CHECK(icm42670_set_gyro_lpf(&dev, ICM42670_GYRO_LFP_53HZ));
    // set output data rate (ODR)
    ESP_ERROR_CHECK(icm42670_set_accel_odr(&dev, ICM42670_ACCEL_ODR_200HZ));
    ESP_ERROR_CHECK(icm42670_set_gyro_odr(&dev, ICM42670_GYRO_ODR_200HZ));
    // set full scale range (FSR)
    ESP_ERROR_CHECK(icm42670_set_accel_fsr(&dev, ICM42670_ACCEL_RANGE_16G));
    ESP_ERROR_CHECK(icm42670_set_gyro_fsr(&dev, ICM42670_GYRO_RANGE_2000DPS));

    // ESP_ERROR_CHECK(icm42670_set_accel_pwr_mode(&dev, ICM42670_ACCEL_ENABLE_LN_MODE));

    // ESP_ERROR_CHECK(icm42670_set_accel_lpf(&dev, ICM42670_ACCEL_LFP_53HZ));
    // ESP_ERROR_CHECK(icm42670_set_accel_odr(&dev, ICM42670_ACCEL_ODR_200HZ));
    // ESP_ERROR_CHECK(icm42670_set_accel_fsr(&dev, ICM42670_ACCEL_RANGE_16G));

    // // Wake up the device and configure accelerometer settings

    // // Power Management - Wake up the IMU from sleep mode
    // WriteRegister(PWR_MGMT0_REG, 0x93);  // Wake up, use internal oscillator (refer to datasheet)

    // // Set accelerometer Output Data Rate (ODR) and bandwidth
    // WriteRegister(ACCEL_CONFIG0_REG, 0x25);  // Example for setting the ODR (refer to datasheet)
    // WriteRegister(ACCEL_CONFIG1_REG, 0x03);  // Example for setting ±4g range (refer to datasheet)
}

void IMU::ReadAllAxes(int16_t* accel_x, int16_t* accel_y, int16_t* accel_z)
{
    ReadAxe_X(accel_x);
    ReadAxe_Y(accel_y);
    ReadAxe_Z(accel_z);
}

void IMU::ReadAxe_X(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_ACCEL_DATA_X1, value);

    ESP_LOGI("IMU", "Accel X: %d", *value);
}

void IMU::ReadAxe_Y(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_ACCEL_DATA_Y1, value);

    ESP_LOGI("IMU", "Accel Y: %d", *value);
}

void IMU::ReadAxe_Z(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_ACCEL_DATA_Z1, value);

    ESP_LOGI("IMU", "Accel Z: %d", *value);
}

void IMU::ReadAllGyros(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z)
{
    ReadAxe_X(gyro_x);
    ReadAxe_Y(gyro_y);
    ReadAxe_Z(gyro_z);

    ESP_LOGI("IMU", "Accel X: %d, Y: %d, Z: %d", *gyro_x, *gyro_y, *gyro_z);
}

void IMU::ReadGyro_X(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_GYRO_DATA_X1, value);

    ESP_LOGI("IMU", "Accel X: %d", *value);
}

void IMU::ReadGyro_Y(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_GYRO_DATA_Y1, value);

    ESP_LOGI("IMU", "Accel Y: %d", *value);
}

void IMU::ReadGyro_Z(int16_t *value)
{   
    icm42670_read_raw_data(&dev, ICM42670_REG_GYRO_DATA_Z1, value);

    ESP_LOGI("IMU", "Accel Z: %d", *value);
}
// void IMU::WriteRegister(uint8_t reg, uint8_t value)
// {
//     uint8_t buffer[2] = { reg, value };
//     i2c->Transmit(deviceAddress, buffer, 2);
// }

// void IMU::ReadRegister(uint8_t reg, uint8_t* buffer, size_t size)
// {
//     i2c->Transmit(deviceAddress, &reg, 1);  // Send the register address
//     i2c->Receive(deviceAddress, buffer, size);  // Read the data
// }
