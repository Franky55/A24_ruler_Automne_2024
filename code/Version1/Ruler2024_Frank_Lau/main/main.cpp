#include "main.h"



#define LED_GPIO (gpio_num_t)20       // GPIO pin for the LED
#define CONTROL_GPIO (gpio_num_t)21   // GPIO pin to be set to LOW

void InitializeProcessus();
void ControleLED();
void gpio_setup();

long counter = 0;
bool ledValue = false;

IMU imu;


extern "C" void app_main(void)
{
    TimeBased timer;
    i2cdev_init();
    InitializeProcessus();
    gpio_setup();

    timer.addTask(&ControleLED);
    timer.addTask(IMU_function);
    imu.Initialize();

    
    TCA9534_IO_EXP io_expWrite;
    io_expWrite.I2C_ADDR = 0x64;
    io_expWrite.i2c_master_port = I2C_NUM_0;
    TCA9534_IO_EXP io_expRead;
    io_expRead.I2C_ADDR = 0x65;
    io_expRead.i2c_master_port = I2C_NUM_0;

    set_all_tca9534_io_pins_direction(&io_expWrite, TCA9534_INPUT);
    
    
    

    while(1)
    {
        int16_t allButtons = get_tca9534_all_io_pin_input_status(&io_expRead);
        
        ESP_LOGI("IO extender", "all inputs: %d", allButtons);
        vTaskDelay(pdMS_TO_TICKS(1000));
        //vTaskDelay(1);
    }
}

void InitializeProcessus()
{
    InitializeIMUProcessus();
}

void ControleLED()
{
    //ESP_LOGI("LED Control", "Were in boys");
    counter++;
    if(counter >= 5000)
    {
        counter = 0;
        ledValue = !ledValue;
        gpio_set_level(GPIO_NUM_20, ledValue);

        // Log the LED state to the console
        ESP_LOGI("LED Control", "LED is now %s", ledValue ? "ON" : "OFF");
    }
}

void gpio_setup() {
    // Configure LED_GPIO as output
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_20), // LED pin
        .mode = GPIO_MODE_OUTPUT,          // Output mode
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // Configure CONTROL_GPIO as output and set it to LOW
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_21); // Control pin
    gpio_config(&io_conf);
    gpio_set_level(GPIO_NUM_21, 0); // Set to LOW
}

void DoNothing(){}