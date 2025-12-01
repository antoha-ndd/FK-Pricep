#pragma once
#include "Objects.h"
#include <WiFiServer.h>



void EmptyOnReceive(WiFiClient *client, String buffer) {};

class TTCPServer : public TControl
{
private:
    bool State{false};
    uint16_t Port;
    WiFiServer Srv;

public:
        
    uint16_t GetPort(){

        return Port;

    };



    TTCPServer( ) : TControl()
    {

     
    };

    void Start(uint16_t _Port ){

        State = true;
        Port = _Port;
        Srv.begin( _Port);
    }

    void Stop(){

        State = false;
        Srv.end();

    }

    bool GetState(){

        return State;

    }

    void Send(String buffer){

        WiFiClient client = Srv.available();
        
        if (client) {

            client.print(buffer);

        }                


    }

    virtual void Idle()
    {
        if(!State) return;

        WiFiClient client = Srv.available();
        
        if (client) {



            while(client.available()>0){
                
                String buffer = client.readString();
                OnReceive( &client , buffer );
                
            }

        }
        
    }

    void (*OnReceive)(WiFiClient *client, String buffer){EmptyOnReceive};

    ~TTCPServer();

};


