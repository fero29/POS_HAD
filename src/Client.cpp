#include "Client.h"

    Client::Client(std::string adr, int port)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0) 
        {
            std::cout<<"Socket creation error \n";
            exit(EXIT_FAILURE); 
        }

        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(port);

        if(inet_pton(AF_INET, adr.c_str(), &serv_addr.sin_addr) <= 0)  
        { 
            std::cout<<"Invalid address/ Address not supported \n"; 
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
            std::cout<<"Connection Failed \n"; 
            exit(EXIT_FAILURE);
        }
        connected = true;
        std::thread(&Client::reader, this).detach();
    }
    
    Client::~Client()
    {
        close(sock);
    }
    
    void Client::sendMsg(Data& msg) 
    {
        int val = send(sock , (void *)&msg, sizeof(msg), 0 ); 
        std::cout<<"message sent "<<val<<"B\n";
    }
    
    Data Client::readMsg() 
    {
        std::unique_lock<std::mutex> mlock(mut);
        while(readBuffer.empty())
        {
            cond.wait(mlock);
        }
        Data dat = readBuffer.front();
        readBuffer.pop();
        return dat;
    }
    
    void Client::exitClient() 
    {
        connected = false;
        delete this;
    }
    
    bool Client::getConnected() 
    {
        return connected;
    }
    
    void Client::reader() 
    {
        while (connected)
        {
            int val = read( sock , buffer, sizeof(buffer)); 
            if(val > 0)
            {
                Data* data = (Data*)buffer;
                std::unique_lock<std::mutex> mlock(mut);
                readBuffer.push(*data);
                std::cout<<"message readed type: "<<data->m_type<<" "<<val<<"B\n";
                mlock.unlock();
                cond.notify_one();
            }
        }
    }