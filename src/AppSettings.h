
#include "var.h"
#include "events.h"

void Init()
{

    LoadSettings();
    setupWiFi();

    App = new TApplication();
    App->Run();

    



    for (size_t i = 0; i < 4; i++)
    {
        Led[i] = new TLed( Inputs[i] );
        Led[i]->Register(App);
        Led[i]->Off();
        
        Blink[i] = new TTimer( );
        Blink[i]->Register(App);
        
    }
    
    Blink[0]->OnTimeout = Blink1;
    Blink[1]->OnTimeout = Blink2;
    Blink[2]->OnTimeout = Blink3;
    Blink[3]->OnTimeout = Blink4;


  
    ui.start();
    ui.attachBuild(build);
    ui.attach(action);

    setupTelnet();    

}
