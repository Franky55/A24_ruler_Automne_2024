#include "I2C_Controller.h"

I2C_Controller::I2C_Controller()
{
    i2c_gpio_sda = GPIO_NUM_2;
    i2c_gpio_scl = GPIO_NUM_3;

    i2c_port = I2C_NUM_0;
    initialize();
}

void I2C_Controller::Transmit(uint8_t deviceAddress, const uint8_t *send_buffer, size_t size)
{
    i2c_master_write_to_device(i2c_port, deviceAddress, send_buffer, size, TIMEOUT_MS);
}

void I2C_Controller::Receive(uint8_t deviceAddress, uint8_t *read_buffer, size_t maxSize)
{
    i2c_master_read_from_device(i2c_port, deviceAddress, read_buffer, maxSize, TIMEOUT_MS);
}

void I2C_Controller::TransmitAndReceive(uint8_t deviceAddress, const uint8_t *send_buffer, size_t sendSize, uint8_t *read_buffer, size_t receiveSize)
{
    Transmit(deviceAddress, send_buffer, sendSize);
    Receive(deviceAddress+1, read_buffer, receiveSize);
}

void I2C_Controller::initialize()
{
    i2c_config_t conf = {
	.mode = I2C_MODE_MASTER,
	.sda_io_num = i2c_gpio_sda,
	.scl_io_num = i2c_gpio_scl,
	.sda_pullup_en = GPIO_PULLUP_ENABLE,
	.scl_pullup_en = GPIO_PULLUP_ENABLE,
	.master = {.clk_speed = 400000,}
    };

    ESP_ERROR_CHECK(i2c_param_config(i2c_port, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0));
}