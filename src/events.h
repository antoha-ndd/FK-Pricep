#include "var.h"



void Button1_OnClick(TButton *Button)
{

};


void LoadSettings()
{

    preferences.begin("config", false);

    data.Port = preferences.getInt("Port", 1883);
    data.MinWaterTemp = preferences.getFloat("MinWaterTemp", 0);
    strcpy(data.MQTTServer, preferences.getString("Server", "").c_str());
    strcpy(data.MQTTTopic, preferences.getString("Topic", "").c_str());

    preferences.end();
}

void build()
{

    LoadSettings();

    GP.BUILD_BEGIN(GP_DARK, 500);

    GP.LABEL("Температура 1 : " );
    GP.LABEL("Температура 2 : " );
    GP.LABEL("Бочка полна : " );
    GP.BREAK();

    GP.BUTTON("SaveBtn", "Сохранить");

    GP_MAKE_BLOCK_TAB("MQTT",
                      GP_MAKE_BOX(
                          GP.LABEL("Cервер");
                          GP.TEXT("MQTTServer", "", data.MQTTServer););

                      GP_MAKE_BOX(
                          GP.LABEL("Порт");
                          GP.NUMBER("MQTTPort", "", data.Port));

                      GP_MAKE_BOX(
                          GP.LABEL("Топик");
                          GP.TEXT("MQTTTopic", "", data.MQTTTopic);););

    GP.BUTTON("RebootBtn", "Перезагрузить");

    GP.BUILD_END();
}

void action()
{

    if (ui.click())
    {

        ui.clickStr("MQTTServer", data.MQTTServer);
        ui.clickStr("MQTTTopic", data.MQTTTopic);
        ui.clickInt("MQTTPort", data.Port);

        if (ui.click("SaveBtn"))
        {

            preferences.begin("config", false);

            preferences.putInt("Port", data.Port);
            preferences.putString("Server", data.MQTTServer);
            preferences.putString("Topic", data.MQTTTopic);

            preferences.end();
            
        }

        if (ui.click("RebootBtn"))
            ESP.restart();
    }
}

void Timer1_Timeout(TTimer *Timer)
{


};



void setupWiFi()
{

    WiFi.softAP("PRICEP");
    
}