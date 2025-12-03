#include "var.h"




/* ------------------------------------------------- */

// (optional) callback functions for telnet events
void onTelnetConnect(String ip) {
  telnet.println("\nWelcome " + telnet.getIP());
}


void onTelnetInput(String str) {
  // checks for a certain command
  if (str == "ping") {
    telnet.println("> pong"); 
  } else if (str == "bye") {
    telnet.println("> disconnecting you...");
    telnet.disconnectClient();
  } else {

    if(str.length()!=2) {
        telnet.println("Error");
        return;
    }
    if(str !="00" && str.toInt()==0){
        telnet.println("Error");
        return;        
    }
    
    String S_led,S_state;
    S_led+=str.charAt(0);
    S_state+=str.charAt(1);

    int led=S_led.toInt();
    int state=S_state.toInt();

    if(led>3 || state>1){
        telnet.println("Error");        
        return;        
    } 

    Led[led]->SetState(state);
    telnet.println("OK");

  }
}


void srv_OnReceive(WiFiClient *client, String buffer) {


};

void setupTelnet() {  
  // passing on functions for various telnet events
  telnet.onConnect(onTelnetConnect);
  telnet.onInputReceived(onTelnetInput);

  Serial.print("- Telnet: ");
  if (telnet.begin(230)) {
    Serial.println("running");
  } else {
    Serial.println("error.");
  }
}

void LoadSettings()
{

    pinMode(8, OUTPUT);
    pinMode(5, INPUT_PULLUP);
    bool res = digitalRead(5);
    if(!res){
        
        preferences.begin("config", false);
        preferences.clear();
        preferences.end();

        for (size_t i = 0; i < 5; i++)
        {
            digitalWrite(8,false);
            delay(300);
            digitalWrite(8,true);
            delay(300);
        }

    }

    preferences.begin("config", false);

    Inputs[0] = preferences.getInt("Inputs1", 1);
    Inputs[1] = preferences.getInt("Inputs2", 2);
    Inputs[2] = preferences.getInt("Inputs3", 3);
    Inputs[3] = preferences.getInt("Inputs4", 4);

    SSID = preferences.getString("SSID", "PRICEP");
    PWD = preferences.getString("PWD", "");

    preferences.end();
    digitalWrite(8,false);

}

void build()
{

    GP.BUILD_BEGIN(GP_DARK, 500);
    GP.UPDATE("Led1,Led2,Led3,Led4");
    GP_MAKE_BLOCK_TAB("Параметры Wi-Fi",
                      GP_MAKE_BOX(
                          GP.LABEL("Имя сети");
                          GP.TEXT("SSID", "", SSID);
                        );
                        GP_MAKE_BOX(
                          GP.LABEL("Пароль");
                          GP.TEXT("PWD", "", PWD);
                        );

    );


    GP_MAKE_BLOCK_TAB("Настройки портов",
                      GP_MAKE_BOX(
                          GP.LABEL("Порт 1");
                          GP.NUMBER("Input1", "", Inputs[0]);
                          GP.BUTTON("Toggle1", "On/Off");
                          GP.BUTTON("Blink1", "Тест");
                          GP.LED("Led1", Led[0]->GetState()););

                      GP_MAKE_BOX(
                          GP.LABEL("Порт 2");
                          GP.NUMBER("Input2", "", Inputs[1]);
                          GP.BUTTON("Toggle2", "On/Off");
                          GP.BUTTON("Blink2", "Тест");
                          GP.LED("Led2", Led[1]->GetState()););

                      GP_MAKE_BOX(
                          GP.LABEL("Порт 3");
                          GP.NUMBER("Input3", "", Inputs[2]);
                          GP.BUTTON("Toggle3", "On/Off");
                          GP.BUTTON("Blink3", "Тест");
                          GP.LED("Led3", Led[2]->GetState()););

                      GP_MAKE_BOX(
                          GP.LABEL("Порт 4");
                          GP.NUMBER("Input4", "", Inputs[3]);
                          GP.BUTTON("Toggle4", "On/Off");
                          GP.BUTTON("Blink4", "Тест");
                          GP.LED("Led4", Led[3]->GetState());););

    GP_MAKE_BOX(
        GP.BUTTON("SaveBtn", "Сохранить");
        GP.BUTTON("RebootBtn", "Перезагрузить"););

    GP.BUILD_END();
}

void action()
{

    if (ui.update("Led1"))
        ui.answer(Led[0]->GetState());
    if (ui.update("Led2"))
        ui.answer(Led[1]->GetState());
    if (ui.update("Led3"))
        ui.answer(Led[2]->GetState());
    if (ui.update("Led4"))
        ui.answer(Led[3]->GetState());

    if (ui.click())
    {

        ui.clickInt("Input1", Inputs[0]);
        ui.clickInt("Input2", Inputs[1]);
        ui.clickInt("Input3", Inputs[2]);
        ui.clickInt("Input4", Inputs[3]);

        ui.clickString("SSID", SSID);
        ui.clickString("PWD", PWD);

        if (ui.click("Toggle1"))
            Led[0]->Toggle();
        if (ui.click("Toggle2"))
            Led[1]->Toggle();
        if (ui.click("Toggle3"))
            Led[2]->Toggle();
        if (ui.click("Toggle4"))
            Led[3]->Toggle();

        if (ui.click("Blink1"))
        {
            if (Blink[0]->GetState())
            {
                Blink[0]->Stop();
                Led[0]->Off();
            }
            else
                Blink[0]->Start(300);
        }
        if (ui.click("Blink2"))
        {
            if (Blink[1]->GetState())
            {
                Blink[1]->Stop();
                Led[1]->Off();
            }
            else
                Blink[1]->Start(300);
        }
        if (ui.click("Blink3"))
        {
            if (Blink[2]->GetState())
            {
                Blink[2]->Stop();
                Led[2]->Off();
            }
            else
                Blink[2]->Start(300);
        }
        if (ui.click("Blink4"))
        {
            if (Blink[3]->GetState())
            {
                Blink[3]->Stop();
                Led[3]->Off();
            }
            else
                Blink[3]->Start(300);
        }

        if (ui.click("SaveBtn"))
        {

            preferences.begin("config", false);

            preferences.putInt("Inputs1", Inputs[0]);
            preferences.putInt("Inputs2", Inputs[1]);
            preferences.putInt("Inputs3", Inputs[2]);
            preferences.putInt("Inputs4", Inputs[3]);


            preferences.putString("SSID", SSID );
            preferences.putString("PWD", PWD );

            preferences.end();
        }

        if (ui.click("RebootBtn"))
            ESP.restart();
    }
}

void Blink1(TTimer *Timer)
{

    Led[0]->Toggle();
};

void Blink2(TTimer *Timer)
{

    Led[1]->Toggle();
};

void Blink3(TTimer *Timer)
{

    Led[2]->Toggle();
};

void Blink4(TTimer *Timer)
{

    Led[3]->Toggle();
};

void setupWiFi()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP( SSID , PWD );
}






