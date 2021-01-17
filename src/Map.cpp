#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::addSnake(Snake snk) 
{
    snakes.push_back(snk);
}

void Map::addApple(Apple apl) 
{
    std::cout<<"adding apl"<<std::endl;
    apples.push_back(apl);
}

void Map::refreshMap() 
{

    for(int i = 0; i < (int)snakes.size(); i++)
    {

        snakes[i].move();
    }

    

    for(int i = 0; i < (int)apples.size(); i++)
    {
        int eat = whoEatApple(apples[i]);
        if(eat != -1)
        {
            snakes[eat].grow();
        }
    }

    drawMap();

}

int Map::whoEatApple(Apple& apl) 
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

void Map::refreshApple(Apple& apl, std::pair<int, int> cor) 
{
    apl.setCoordinates(cor);
}

Apple& Map::getApple(int index) 
{
    return apples[index];
}

Snake& Map::getSnake(int index) 
{
    return snakes[index];
}

void Map::clearScreen() 
{
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void Map::drawMap() 
{
    for (size_t y = 0; y < MAP_SIZE; y++)
    {
        for (size_t x = 0; x < MAP_SIZE; x++)
        {
            map[x][y] = BACKGROUND_CHAR;
        }
    }

    for (size_t i = 0; i < (size_t)snakes.size(); i++)
    {
        for (size_t j = 0; j < (size_t)snakes[i].getSize(); j++)
        {
            std::pair<int, int> piece = snakes[i].getPiece(j);
            map[piece.first][piece.second] = SNAKE_CHAR;
        }
    }

    for (size_t i = 0; i < (size_t)apples.size(); i++)
    {
        std::pair<int, int> appCor = apples[i].getCoordinates();
        map[appCor.first][appCor.second] = APPLE_CHAR;
    }

    //-------------------------------------------------------------------

    //clearScreen();

    for (size_t i = 0; i < MAP_SIZE + 2; i++)
    {
        std::cout<<"-";
    }

    std::cout<<"\n";
    

    for (size_t y = 0; y < MAP_SIZE; y++)
    {
        std::cout<<"|";
        for (size_t x = 0; x < MAP_SIZE; x++)
        {
            std::cout<<map[x][y];
        }

        std::cout<<"|\n";       
    }

    for (size_t i = 0; i < MAP_SIZE + 2; i++)
    {
        std::cout<<"-";
    }

    std::cout<<"\n";    
}