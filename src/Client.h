#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <queue>
#include "Data.h"
#include <mutex>
#include <condition_variable>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 4096
#define ADDRESS "127.0.0.1"


     
    

    class Client
    {
    private:
        int sock = 0;
        sockaddr_in serv_addr;
        char buffer[BUFFER_SIZE];
        std::queue<Data> readBuffer;
        std::mutex mut;
        std::condition_variable cond;
        void reader();
        bool connected = false;
    public:
        Client(std::string adr, int port);
        ~Client();
        void sendMsg(Data& msg);
        Data readMsg();
        void exitClient();
        bool getConnected();

    };
    

    
    #endif // __CLIENT_H__