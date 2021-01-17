#ifndef __SERVER_H__
#define __SERVER_H__


#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream> 
#include <vector>
#include "Data.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_CLIENTS 10 


class Server
{
private:
    int server_fd;
    std::vector<int> client_socket;
    std::vector<std::queue<Data> > readBuffer;
    sockaddr_in address;
    char buffer[BUFFER_SIZE];
    void acceptConnection();
    bool serverRunning = false;
    void reader();
    std::mutex mut;
    std::condition_variable cond;

public:
    Server(int port);
    ~Server();
    void sendMsg(int index, Data& msg);
    void sendToAll(Data& msg);
    Data readMsg(int index);
    void stopServer();
    int getSocketClient(int i);
    int getNumberOfClients();
    bool running();
};
    

    #endif // __SERVER_H__