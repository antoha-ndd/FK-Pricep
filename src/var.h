
#pragma once
#define GH_NO_PAIRS

#include <espwifi.h>
#include "Objects.h"
#include "ObjectTimer.h"
#include <GyverPortal.h>
#include <Preferences.h>
#include "led.h"
#include "ESPTelnet.h"



GyverPortal ui;
Preferences preferences;
ESPTelnet telnet;

TApplication *App;
TLed *Led[4];

TTimer *Blink[4];

int Inputs[4]{0,0,0,0};

String SSID, PWD;
