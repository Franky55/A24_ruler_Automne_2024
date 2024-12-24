#include "IO_Expender.h"

#define I2C_MASTER_SCL_IO           3      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           2      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */

IO_Expender::IO_Expender(int8_t Read_Address)
{
    read_address = Read_Address;

    io_expWrite.I2C_ADDR = read_address - 1;
    io_expWrite.i2c_master_port = I2C_NUM_0;

    io_expRead.I2C_ADDR = read_address;
    io_expRead.i2c_master_port = I2C_NUM_0;
}

esp_err_t IO_Expender::i2c_master_init() {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_param_config(I2C_NUM_0, &conf);

    return i2c_driver_install(I2C_NUM_0, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void IO_Expender::set_pin_direction(TCA9534_PINS Pin, TCA9534_PORT_DIRECTION Dir)
{
    // Exemple de dir TCA9534_INPUT
    set_tca9534_io_pin_direction(&io_expWrite, Pin, Dir);
}

void IO_Expender::set_pin_direction(TCA9534_PORT_DIRECTION Dir)
{
    // Exemple de dir TCA9534_INPUT
    set_all_tca9534_io_pins_direction(&io_expWrite, Dir);
}

int16_t IO_Expender::get_pin_status(TCA9534_PINS Pin)
{
    // Exemple de value des Pin TCA9534_IO2
    int16_t value = get_io_pin_input_status(&io_expRead, Pin);
    return value;
}

void IO_Expender::set_pin_status(TCA9534_PINS Pin, int8_t state)
{
    set_tca9534_io_pin_output_state(&io_expWrite, Pin, state);
}