#include "Snake.h"


Snake::Snake(std::pair<int, int> cor, int mapSize) : direct (right)
{
    snake.push_back(cor);
    this->mapSize = mapSize;
}

Direction Snake::getDirect() 
{
    return direct;
}

void Snake::setDirect(Direction dir) 
{
    this->direct = dir;
}

std::pair<int, int> Snake::getNext(std::pair<int, int> now, Direction dir) 
{
    std::pair<int, int> next = now;

    switch (dir)
    {
        case up:
        {
            next.second = (int)(next.second - 1) % mapSize;
            if(next.second < 0 ) next.second = mapSize + next.second;
            return next;
        }
            break;
        
        case down:
        {
            next.second = (int)(next.second + 1) % mapSize;
            if(next.second < 0 ) next.second = mapSize + next.second;
            return next;
        }
            break;

        case left:
        {
            next.first = (int)(next.first - 1) % mapSize;
            if(next.first < 0 ) next.first = mapSize + next.first;
            return next;
        }
            break;

        case right:
        {
            next.first = (int)(next.first + 1) % mapSize;
            if(next.first < 0 ) next.first = mapSize + next.first;
            return next;
        }
            break;

        default:
        {
            return next;
        }
    }
}

std::pair<int, int> Snake::getHead() 
{
    return snake.front();
}

int Snake::getSize() 
{
    return snake.size();
}

std::pair<int, int> Snake::getPiece(int i) 
{
    return snake[i];
}

void Snake::move() 
{
    snake.push_front(getNext(snake.front(), direct));
    snake.pop_back();
}

void Snake::grow() 
{
    snake.push_front(getNext(snake.front(), direct));
}
