
#pragma once
#define GH_NO_PAIRS

#include <espwifi.h>
#include "Objects.h"
#include "ObjectTimer.h"
#include "button.h"
#include "varbasetypes.h"
#include <GyverPortal.h>
#include <Preferences.h>
#include "led.h"



GyverPortal ui;
Preferences preferences;

TApplication *App;
TButton *Btn[5];
TButton *PumpBtn;
TLed *Led[5];
TTimer *Timer1, *TimerMQTT;
TOutputDevice *Pump;
TButton *Limiter;




struct Data
{
    int Port;
    char MQTTServer[100];
    char MQTTTopic[100];
    float MinWaterTemp;
};

Data data;
