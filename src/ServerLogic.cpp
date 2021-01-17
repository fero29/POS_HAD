#include "ServerLogic.h"

ServerLogic::ServerLogic(int players) : server(PORT)
{
    initGame(players);
    startReader();
    serverRuntime();
}

void ServerLogic::refreshApple(Apple& apl, int index) 
{
    apl.setCoordinates(std::pair<int, int>(std::rand() % MAP_SIZE, std::rand() % MAP_SIZE));
    Data data(appleType, apl.getCoordinates(), index);
    server.sendToAll(data);
}

void ServerLogic::serverRuntime() 
{
    std::cout<<"in server runtime"<<std::endl;
    while(server.running())
    {
        serverStep();
        stepPause();
    }
}

void ServerLogic::serverStep() 
{
    for (size_t i = 0; i < apples.size(); i++)
    {
        int eat = whoEatApple(apples[i]);
        if(eat != -1)
        {
            snakes[eat].grow();
            refreshApple(apples[i], i);
        }
    }

    for (size_t i = 0; i < snakes.size(); i++)
    {
        snakes[i].move();
    }    
}

void ServerLogic::stepPause() 
{
    usleep(GAME_SPEED);
}


void ServerLogic::initGame(int players) 
{
    std::srand(std::time(nullptr));

    while ((int)snakes.size() < players)
    {
        if(server.getNumberOfClients() > (int)snakes.size())
        {
            std::unique_lock<std::mutex> mlock(mut);
            snakes.push_back(Snake(std::pair<int, int>(std::rand() % MAP_SIZE, std::rand() % MAP_SIZE), right));
            std::cout<<"added snake"<<std::endl;

            for (size_t i = 0; i < (size_t)server.getNumberOfClients()-1; i++)
            {
                Data data(initType, snakes[i].getDirect(), i, snakes[i].getHead());
                server.sendMsg(server.getNumberOfClients()-1, data);
            }

            Data data((MessageType)0, right, server.getNumberOfClients()-1, snakes[snakes.size()-1].getHead());
            server.sendToAll(data);
            std::cout<<"sended snake to all"<<std::endl;
            mlock.unlock();
        }
    }

    stepPause();
    initApples(APPLES_COUNT);
    std::cout<<"added apple"<<std::endl;
}

void ServerLogic::initApples(int count) 
{
    for (int i = 0; i < count; i++)
    {
        Apple apl(std::pair<int, int>(std::rand() % MAP_SIZE, std::rand() % MAP_SIZE));
        apples.push_back(apl);
        Data data(appleType, apl.getCoordinates(), i);
        server.sendToAll(data);
    }
}

void ServerLogic::serverReader(int index) 
{
    while(this->server.running())
    {
        Data data = server.readMsg(index);

        switch (data.m_type)
        {
        case directType:
            {
                std::cout<<"readed direct, send to all \n";
                data.m_snakeIndex = index;
                server.sendToAll(data);
            }
            break;

        case appleType:
            {
                
            }
            break;
        
        default:
            break;
        }
    }
}

int ServerLogic::whoEatApple(Apple& apl) 
{
    for(int i = 0; i < (int)snakes.size(); i++)
    {
        if(snakes[i].getHead() == apl.getCoordinates())
        {
            return i;
        }
    }
    return -1;
}

void ServerLogic::startReader() 
{
    for (size_t i = 0; i < (size_t)server.getNumberOfClients(); i++)
    {
        std::cout<<"reader n "<<i<<std::endl;
        std::thread(&ServerLogic::serverReader, this, i).detach();
    }    
    
}