#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "Snake.h"
#include "Apple.h"
#include <array>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <ctime>

#define MAP_SIZE 10
#define APPLE_CHAR (char)'A'
#define SNAKE_CHAR (char)'S'
#define BACKGROUND_CHAR (char)' '


class Map
{
private:
    std::array<std::array<char, MAP_SIZE>, MAP_SIZE> map;
    std::vector<Snake> snakes;
    std::vector<Apple> apples;
    void drawMap();
    int whoEatApple(Apple& apl);
    void clearScreen();


public:
    Map();
    ~Map();

    void addSnake(Snake snk);
    void addApple(Apple apl);
    void refreshMap();
    void refreshApple(Apple& apl, std::pair<int, int> cor);
    Apple& getApple(int index);
    Snake& getSnake(int index);
    
    
};



#endif // __MAP_H__