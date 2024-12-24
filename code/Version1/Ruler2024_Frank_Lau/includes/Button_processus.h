#ifndef BUTTON_PROCESSUS_H
#define BUTTON_PROCESSUS_H

#include "main.h"
#include "esp_log.h"
#include "IO_Expender.h"

//Global variables
extern void (*Buttons_function)(void);


typedef enum {
    Button_Up = 1,
    Button_Right,
    Button_Left,
    Button_Down,
    Button_Center,
} Buttons;

//Functions
void InitializeButtons();
void GetAllButtons();

//variables
extern IO_Expender expender;

#endif