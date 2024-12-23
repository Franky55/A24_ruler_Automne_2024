#ifndef I2C_CONTROLLER
#define I2C_CONTROLLER

#include <string.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"
#include "driver/i2c.h"
#include "icm42670.h"

#define TIMEOUT_MS		1000



class I2C_Controller {
public:
    // Constructor
    I2C_Controller();
    void Transmit(uint8_t deviceAddress, const uint8_t *send_buffer, size_t size);
    void Receive(uint8_t deviceAddress, uint8_t *read_buffer, size_t maxSize);
    void TransmitAndReceive(uint8_t deviceAddress, const uint8_t *send_buffer, size_t sendSize, uint8_t *read_buffer, size_t receiveSize);


    void initialize();
private:
    gpio_num_t i2c_gpio_sda;
    gpio_num_t i2c_gpio_scl;

    i2c_port_t i2c_port;

};

#endif