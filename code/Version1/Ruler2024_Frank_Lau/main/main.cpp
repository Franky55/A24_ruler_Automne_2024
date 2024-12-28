#include "main.h"


#define LED_GPIO (gpio_num_t)20       // GPIO pin for the LED
#define CONTROL_GPIO (gpio_num_t)21   // GPIO pin to be set to LOW

void InitializeProcessus();
void ControleLED();
void gpio_setup();
void SensorDistance();

long counter = 0;
bool ledValue = false;
VL53L5CX_Configuration Dev; // Sensor configuration

extern "C" void app_main(void)
{
    TimeBased timer;
    
    i2cdev_init();
    InitializeProcessus();
    gpio_setup();

    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init_softap();
    start_webserver();

    timer.addTask(&ControleLED);
    timer.addTask(IMU_function);
    timer.addTask(Buttons_function);

    ESP_LOGI("", "Distance sensor starting");

    vTaskDelay(pdMS_TO_TICKS(500));
    // SensorDistance();    

    // uint8_t status, isReady;
    
    // VL53L5CX_ResultsData Results; // Results data from VL53L5CX
    // vl53l5cx_start_ranging(&Dev);

    while(1)
    {
        // vl53l5cx_check_data_ready(&Dev, &isReady);

        // ESP_LOGI("Polling", "isReady %d", isReady);

        // if(isReady)
        // {
        //     vl53l5cx_get_ranging_data(&Dev, &Results);

        //     /* As the sensor is set in 4x4 mode by default, we have a total
        //      * of 16 zones to print. For this example, only the data of first zone are
        //      * print */
        //     ESP_LOGI("", "Print data no : %3u\n", Dev.streamcount);
        //     for(int i = 0; i < 16; i++)
        //     {
        //         ESP_LOGI("", "Zone : %3d, Status : %3u, Distance : %4d mm\n",
        //                i,
        //                Results.target_status[VL53L5CX_NB_TARGET_PER_ZONE*i],
        //                Results.distance_mm[VL53L5CX_NB_TARGET_PER_ZONE*i]);
        //     }
        //     ESP_LOGI("", "\n");
        //     vTaskDelay(pdMS_TO_TICKS(1000));
        // }

        // /* Wait a few ms to avoid too high polling (function in platform
        //  * file, not in API) */
        // WaitMs(&(Dev.platform), 5);


        // vTaskDelay(pdMS_TO_TICKS(1000));
        vTaskDelay(1);
    }
}

void InitializeProcessus()
{
    InitializeIMUProcessus();
    InitializeButtons();
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

void SensorDistance()
{
    uint8_t status, isAlive;
    
    VL53L5CX_ResultsData Results; // Results data from VL53L5CX
    // Fill the platform structure with customer's implementation.
    Dev.platform.address = VL53L5CX_DEFAULT_I2C_ADDRESS;
    Dev.platform.port = I2C_NUM_0;

    // Power on sensor and init
    ESP_LOGI("", "Checking if chip is alive");
    vTaskDelay(pdMS_TO_TICKS(5000));
    status = vl53l5cx_is_alive(&Dev, &isAlive);

    // Init VL53L5CX sensor
    status = vl53l5cx_init(&Dev);
    ESP_LOGI("VL53L5CX", "VL53L5CX ULD ready! (Version: %s)", VL53L5CX_API_REVISION);
}
