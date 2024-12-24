#ifndef IO_EXPENDER_H
#define IO_EXPENDER_H

#include "TCA9534.h"
#include "esp_log.h"
#include "driver/i2c.h"

class IO_Expender
{

public:
    IO_Expender(int8_t Read_Address);
    esp_err_t i2c_master_init();
    void set_pin_direction(TCA9534_PINS Pin, TCA9534_PORT_DIRECTION Dir);
    void set_pin_direction(TCA9534_PORT_DIRECTION Dir);
    int16_t get_pin_status(TCA9534_PINS Pin);
    void set_pin_status(TCA9534_PINS Pin, int8_t state);

private:
    int8_t read_address;
    TCA9534_IO_EXP io_expWrite;
    TCA9534_IO_EXP io_expRead;
};

#endif