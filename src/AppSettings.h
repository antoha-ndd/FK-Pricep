
#include "var.h"
#include "events.h"

void Init()
{
    setupWiFi();

    //LoadSettings();/*
    
    App = new TApplication();
    App->Run();
/*
    Btn[0] = new TButton(21, true); //18
    Btn[0]->OnPress = Button1_OnClick;
    Btn[0]->Register(App);


    Led[0] = new TLed(16); //2
    Led[0]->Off();

    PumpBtn = new TButton(1);

    ui.start();
    ui.attachBuild(build);
    ui.attach(action);

   // LoadSettings();

    Timer1 = new TTimer();
    Timer1->Register(App);
    Timer1->Start(100);
    Timer1->OnTimeout = Timer1_Timeout;*/



}
