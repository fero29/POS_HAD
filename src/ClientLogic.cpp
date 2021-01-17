#include "ClientLogic.h"

ClientLogic::ClientLogic(): client(ADDRESS, PORT)
{
    std::thread(&ClientLogic::messageReader, this).detach();
    std::thread(&ClientLogic::readKey, this).detach();
    gameRuntime();
}

void ClientLogic::readKey() 
{   
    char cl;
     
    while(!gameRunning);
    while(gameRunning)
    {
        cl = getch();

        switch (cl)
        {
        case 'w':
        {
            Data data(directType, up);
            client.sendMsg(data);
        }
            break;

        case 's':
        {
            Data data(directType, down);
            client.sendMsg(data);
        }
            break;

        case 'a':
        {
            Data data(directType, left);
            client.sendMsg(data);
        }
            break;

        case 'd':
        {
            Data data(directType, right);
            client.sendMsg(data);
        }
            break;
        
        default:
            break;
        }
    }
    
}

void ClientLogic::messageReader() 
{
    std::cout<<"client message reader\n";
    while(client.getConnected())
    {
        Data data = client.readMsg();
    
        switch (data.m_type)
        {
            case initType:
            {
                map.addSnake(Snake(data.m_snakeCoordinates, MAP_SIZE));
                std::cout<<"client add snake\n";
            }
                break;

            case directType:
            {
                map.getSnake(data.m_snakeIndex).setDirect(data.m_direction);
                std::cout<<"client set direct\n";
            }
                break;

            case appleType:
            {
                if(!gameRunning)
                {
                    map.addApple(Apple(data.m_appleCord));
                    std::cout<<"add apple\n";
                    gameRunning = true;
                }
                else
                {
                    map.refreshApple(map.getApple(data.m_appleIndex), data.m_appleCord);
                    std::cout<<"client refresh apple\n";
                }
                
            }
                break;
            
            default:
                break;
        }
    }
}

void ClientLogic::stepPause() 
{
    usleep(GAME_SPEED);
}

void ClientLogic::gameRuntime() 
{
    while(!gameRunning);
    while(gameRunning)
    {
        map.refreshMap();
        stepPause();
    }
    
}


//https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed

char ClientLogic::getch()
{
        char buf = 0;
        termios old;
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
