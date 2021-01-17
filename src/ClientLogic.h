#ifndef __CLIENTLOGIC_H__
#define __CLIENTLOGIC_H__



#include "Map.h"
#include <iostream>
#include "Client.h"
#include "Data.h"
#include <unistd.h>
#include <termios.h>


class ClientLogic
{
private:
    Map map;
    bool gameRunning = false;
    Client client;
    int id;
public:
    ClientLogic();
    void readKey();
    void messageReader();
    void stepPause();
    void gameRuntime();
    char getch(); 

};



#endif // __CLIENTLOGIC_H__