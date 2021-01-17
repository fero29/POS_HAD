#include "Apple.h"



Apple::Apple(std::pair<int, int> cor) 
{
    setCoordinates(cor);
}

void Apple::setCoordinates(std::pair<int, int> cor) 
{
    coordinates = cor;
}

std::pair<int, int> Apple::getCoordinates() 
{
    return coordinates;
}
