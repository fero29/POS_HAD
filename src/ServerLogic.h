#ifndef __SERVERLOGIC_H__
#define __SERVERLOGIC_H__

#include "Server.h"
#include "Snake.h"
#include "Apple.h"
#include "Map.h"
#include <vector>
#include <unistd.h>

#define APPLES_COUNT 1



class ServerLogic
{
private:
    Server server;
    std::vector<Snake> snakes;
    std::vector<Apple> apples;
    void initGame(int players);
    void initApples(int count);
    void serverReader(int index);
    int whoEatApple(Apple& apl);
    void startReader();
    std::mutex mut;

public:
    ServerLogic(int players);
    void refreshApple(Apple& apl, int index);
    void serverRuntime();
    void serverStep();
    void stepPause();
    
};



#endif // __SERVERLOGIC_H__