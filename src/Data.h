#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <functional>

#define GAME_SPEED 1000000 //microseconds between step

enum Direction
{
    up = 0,
    down = 1,
    left = 2,
    right = 3
};

enum MessageType
{
    initType = 0,
    directType = 1,
    appleType = 2
};

class Data
{
private:


public:
    MessageType m_type;
    Direction m_direction;

    std::pair<int, int> m_snakeCoordinates;
    std::pair<int, int> m_appleCord;
    int m_appleIndex;
    int m_snakeIndex;

    //init
    Data(MessageType type, Direction dir, int snakeIndex, std::pair<int, int> cor);
    //game play-change dir
    Data(MessageType type, Direction dir);
    //gameplay- change apple
    Data(MessageType type, std::pair<int, int> cor, int appleIndex);
    

};

#endif // __DATA_H__