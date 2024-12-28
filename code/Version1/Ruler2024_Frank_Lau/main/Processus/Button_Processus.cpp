#include "Button_Processus.h"

void SetUpXshut();

void (*Buttons_function)(void);
IO_Expender expender(0x20);

//State: 0
void InitializeButtons()
{
    expender.i2c_master_init();
    expender.set_pin_direction(TCA9534_INPUT);
    expender.set_pin_direction((TCA9534_PINS)XShut, TCA9534_OUTPUT);
    expender.set_pin_status((TCA9534_PINS)XShut, 0);
    
    Buttons_function = SetUpXshut;//For reading the data
    //Buttons_function = DoNothing;//Do nothing
}

void SetUpXshut()
{
    static int count = 0;
    count++;
    if(count < 10)
        return;
    expender.set_pin_status((TCA9534_PINS)XShut, 1);
    Buttons_function = GetAllButtons;//For reading the data
}

//State: 1
void GetAllButtons()
{
    static long counter = 0;
    counter++;

    if(counter >= 1000)//1 fois seconde
    {
        counter =0;
        int16_t up = expender.get_pin_status((TCA9534_PINS)Button_Up);
        int16_t right = expender.get_pin_status((TCA9534_PINS)Button_Right);
        int16_t down = expender.get_pin_status((TCA9534_PINS)Button_Down);
        int16_t left = expender.get_pin_status((TCA9534_PINS)Button_Left);
        int16_t center = expender.get_pin_status((TCA9534_PINS)Button_Center);
        
        ESP_LOGI("IO extender", "UP: %d, Right: %d, Down: %d, Left: %d, Center: %d", up,right,down,left,center);
    }
}