#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <deque>
#include "Data.h"



class Snake
{
private:
    std::deque<std::pair<int, int>> snake;
    Direction direct;
    int mapSize;
public:
    Snake(std::pair<int, int> cor, int mapSize);
    Direction getDirect();
    void setDirect(Direction dir);
    std::pair<int, int> getNext(std::pair<int, int> now, Direction dir);
    std::pair<int, int> getHead();
    int getSize();
    std::pair<int, int> getPiece(int i);
    void move();
    void grow();
};


#endif // __SNAKE_H__