#ifndef __APPLE_H__
#define __APPLE_H__

#include <utility>


class Apple
{
private:
    std::pair<int, int> coordinates;
public:
    Apple(std::pair<int, int> cor);
    void setCoordinates(std::pair<int, int> cor);
    std::pair<int, int> getCoordinates();
};


#endif // __APPLE_H__