#include "Server.h"

Server::Server(int port): readBuffer(MAX_CLIENTS)
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        std::cout<<"socket failed"; 
        exit(EXIT_FAILURE); 
    } 
    
    int opt = 1;
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        std::cout<<"setsockopt"; 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        std::cout<<"bind failed"; 
        exit(EXIT_FAILURE); 
    }

    serverRunning = true;

    std::thread(&Server::acceptConnection, this).detach();
    std::thread(&Server::reader, this).detach();
}

Server::~Server()
{
    close(server_fd);

    for(int i = 0; i < (int)client_socket.size(); i++)
    {
        close(client_socket[i]);
    }
}

void Server::acceptConnection() 
{
    while(serverRunning)
    {
        if (listen(server_fd, MAX_CLIENTS) < 0) 
        { 
            std::cout<<"listen error"; 
            exit(EXIT_FAILURE); 
        }

        int addrlen = sizeof(address); 
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if ( new_socket < 0) 
        { 
            std::cout<<"accept error"; 
            exit(EXIT_FAILURE); 
        } 

        client_socket.push_back(new_socket);
    }
}

void Server::sendMsg(int index, Data& msg) 
{
    int val = send(client_socket[index], &msg, sizeof(msg), 0); 
    std::cout<<"message sent type: "<<msg.m_type<<" "<<val<<"B\n"; 
}

void Server::sendToAll(Data& msg) 
{
    for(int i = 0; i < (int)client_socket.size(); i++)
    {
        sendMsg(i, msg);
    }
}

Data Server::readMsg(int index) 
{
    
    std::unique_lock<std::mutex> mlock(mut);
    while(readBuffer[index].empty())
    {
        cond.wait(mlock);
    }
    Data dat = readBuffer[index].front();
    readBuffer[index].pop();
    return dat;
}
void Server::stopServer() 
{
    serverRunning = false;
    delete this;
}

int Server::getSocketClient(int i) 
{
    return client_socket[i];
}

int Server::getNumberOfClients() 
{
    return client_socket.size();
}

bool Server::running() 
{
    return serverRunning;
}

void Server::reader() 
    {
        while (serverRunning)
        {
            for(int i = 0; i < getNumberOfClients(); i++)
            {
                int val = read( client_socket[i] , buffer, sizeof(buffer));
                if(val > 0)
                {
                    std::cout<<"message readed "<<val<<"B\n";
                    Data* data = (Data*)buffer;
                    std::unique_lock<std::mutex> mlock(mut);
                    readBuffer[i].push(*data);
                    mlock.unlock();
                    cond.notify_one();
                }
            }
        }
    }